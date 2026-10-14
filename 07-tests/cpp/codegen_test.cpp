#include "nudl/codegen.hpp"
#include "nudl/lexer.hpp"
#include "nudl/parser.hpp"
#include <cassert>
#include <string>

static std::string compile_cpp(const std::string& src) {
    nudl::Diagnostics diagnostics;
    nudl::Parser parser(nudl::lex(src), diagnostics);
    auto program = parser.parse();
    assert(diagnostics.ok());
    return nudl::generate_source(*program, {nudl::TargetLanguage::Cpp});
}

int main() {
    const std::string basic = R"(fn main() -> i64 {
    print("Hello, world!");
    return 0;
})";
    const auto output = compile_cpp(basic);
    assert(output.find("#include <iostream>") != std::string::npos);
    assert(output.find("Hello, world!") != std::string::npos);
    assert(output.find("int main()") != std::string::npos);

    const std::string escaped = R"(fn main() {
    print("first\nsecond \"quoted\"");
})";
    const auto escaped_output = compile_cpp(escaped);
    assert(escaped_output.find("first\\nsecond \\\"quoted\\\"") != std::string::npos);

    const std::string branch = R"(fn main() {
    if (true) { print("yes"); } else { print("no"); }
})";
    const auto branch_output = compile_cpp(branch);
    assert(branch_output.find(" else {") != std::string::npos);
    return 0;
}
