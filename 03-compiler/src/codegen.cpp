#include "nudl/codegen.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <type_traits>

namespace nudl {
namespace {
std::string type_cpp(const std::string& t) {
    if (t == "i8" || t == "i16" || t == "i32" || t == "i64" ||
        t == "u8" || t == "u16" || t == "u32" || t == "u64" ||
        t == "int" || t == "integer") return "long long";
    if (t == "f32" || t == "f64" || t == "float" || t == "double") return "double";
    if (t == "bool") return "bool";
    if (t == "text" || t == "string") return "std::string";
    if (t == "void") return "void";
    if (t.ends_with("[]")) return "std::vector<" + type_cpp(t.substr(0, t.size() - 2)) + ">";
    return "auto";
}

std::string escape_cpp_string(const std::string& value) {
    std::string out;
    out.reserve(value.size() + 2);
    for (unsigned char c : value) {
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            case '\0': out += "\\0"; break;
            default: out += static_cast<char>(c); break;
        }
    }
    return out;
}

std::string lit(const Literal& x) {
    if (x.kind == Literal::Kind::String) return "\"" + escape_cpp_string(x.value) + "\"";
    if (x.kind == Literal::Kind::Boolean) return x.value;
    if (x.kind == Literal::Kind::Null) return "nullptr";
    return x.value;
}

std::string expr(const Expr& e) {
    return std::visit([](auto const& n) -> std::string {
        using T = std::decay_t<decltype(n)>;
        if constexpr (std::is_same_v<T, Literal>) return lit(n);
        else if constexpr (std::is_same_v<T, Name>) return n.value;
        else if constexpr (std::is_same_v<T, Unary>) return "(" + n.op + expr(*n.rhs) + ")";
        else if constexpr (std::is_same_v<T, Binary>) return "(" + expr(*n.lhs) + " " + n.op + " " + expr(*n.rhs) + ")";
        else if constexpr (std::is_same_v<T, Call>) {
            std::string s = n.callee + "(";
            for (std::size_t i = 0; i < n.args.size(); ++i) {
                if (i) s += ", ";
                s += expr(*n.args[i]);
            }
            return s + ")";
        } else if constexpr (std::is_same_v<T, Array>) {
            throw std::runtime_error("C++ backend does not yet lower array literals");
        } else {
            throw std::runtime_error("C++ backend encountered an unsupported expression");
        }
    }, e.node);
}

void emit_stmt(std::ostringstream& out, const Stmt& stmt, int indent) {
    const std::string pad(static_cast<std::size_t>(indent) * 4, ' ');
    std::visit([&](auto const& node) {
        using T = std::decay_t<decltype(node)>;
        if constexpr (std::is_same_v<T, Binding>) {
            out << pad << (node.constant ? "const auto " : "auto ") << node.name << " = " << expr(*node.value) << ";\n";
        } else if constexpr (std::is_same_v<T, Return>) {
            out << pad << "return " << expr(*node.value) << ";\n";
        } else if constexpr (std::is_same_v<T, ExprStmt>) {
            if (const auto* call = std::get_if<Call>(&node.value->node); call && call->callee == "print") {
                for (std::size_t i = 0; i < call->args.size(); ++i) {
                    if (i) out << pad << "std::cout << ' ';\n";
                    out << pad << "std::cout << " << expr(*call->args[i]) << ";\n";
                }
                out << pad << "std::cout << std::endl;\n";
            } else {
                out << pad << expr(*node.value) << ";\n";
            }
        } else if constexpr (std::is_same_v<T, If>) {
            out << pad << "if (" << expr(*node.condition) << ") {\n";
            for (const auto& child : node.then_branch) emit_stmt(out, *child, indent + 1);
            out << pad << "}";
            if (!node.else_branch.empty()) {
                out << " else {\n";
                for (const auto& child : node.else_branch) emit_stmt(out, *child, indent + 1);
                out << pad << "}";
            }
            out << "\n";
        } else if constexpr (std::is_same_v<T, While>) {
            out << pad << "while (" << expr(*node.condition) << ") {\n";
            for (const auto& child : node.body) emit_stmt(out, *child, indent + 1);
            out << pad << "}\n";
        }
    }, stmt.node);
}

void emit_function(std::ostringstream& out, const Function& fn) {
    const bool is_main = fn.name == "main";
    const std::string return_type = is_main ? "int" : type_cpp(fn.return_type);
    out << return_type << " " << fn.name << "(";
    for (std::size_t i = 0; i < fn.params.size(); ++i) {
        if (i) out << ", ";
        out << type_cpp(fn.params[i].type) << " " << fn.params[i].name;
    }
    out << ") {\n";
    for (const auto& stmt : fn.body) emit_stmt(out, *stmt, 1);
    const bool has_return = !fn.body.empty() && std::holds_alternative<Return>(fn.body.back()->node);
    if (is_main && !has_return) out << "    return 0;\n";
    out << "}\n\n";
}
} // namespace

std::string target_name(TargetLanguage target) {
    switch (target) {
        case TargetLanguage::Cpp: return "cpp";
        case TargetLanguage::C: return "c";
        case TargetLanguage::Rust: return "rust";
        case TargetLanguage::Python: return "python";
        case TargetLanguage::JavaScript: return "javascript";
        case TargetLanguage::TypeScript: return "typescript";
        case TargetLanguage::CSharp: return "csharp";
        case TargetLanguage::Java: return "java";
        case TargetLanguage::Swift: return "swift";
    }
    return "unknown";
}

std::string generate_source(const Program& program, const CodegenOptions& options) {
    if (options.target != TargetLanguage::Cpp) {
        throw std::runtime_error("only the C++ backend is implemented; other targets are registered for staged implementation");
    }

    std::ostringstream out;
    out << "#include <iostream>\n#include <string>\n#include <vector>\n\n";

    for (const auto& fn : program.functions) emit_function(out, fn);

    const bool has_main = std::any_of(program.functions.begin(), program.functions.end(),
        [](const Function& fn) { return fn.name == "main"; });
    if (!has_main) {
        out << "int main() {\n";
        for (const auto& stmt : program.statements) emit_stmt(out, *stmt, 1);
        out << "    return 0;\n}\n";
    } else {
        for (const auto& stmt : program.statements) emit_stmt(out, *stmt, 0);
    }
    return out.str();
}
} // namespace nudl
