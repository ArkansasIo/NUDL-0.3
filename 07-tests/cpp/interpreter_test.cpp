#include "nudl/interpreter.hpp"
#include "nudl/lexer.hpp"
#include "nudl/parser.hpp"
#include <cassert>

int main() {
    const char* source = R"(fn main() -> i64 {
        let n: i64 = 0;
        while (n < 3) {
            n = n + 1;
        }
        return n;
    })";
    auto tokens = nudl::lex(source);
    nudl::Diagnostics diagnostics;
    nudl::Parser parser(std::move(tokens), diagnostics);
    auto program = parser.parse();
    assert(diagnostics.ok());
    nudl::Interpreter vm(*program);
    assert(nudl::runtime_value_to_string(vm.run()) == "3");
    return 0;
}
