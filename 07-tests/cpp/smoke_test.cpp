#include "nudl/lexer.hpp"
#include "nudl/parser.hpp"
#include <cassert>
#include <iostream>
#include <string>

int main() {
    auto tokens = nudl::lex("fn add(a: i64, b: i64) -> i64 { return a + b; }");
    assert(!tokens.empty());
    nudl::Diagnostics diagnostics;
    nudl::Parser parser(std::move(tokens), diagnostics);
    auto program = parser.parse();
    assert(diagnostics.ok());
    assert(program->functions.size() == 1);
    assert(program->functions[0].name == "add");

    const auto escaped = nudl::lex("\"line\\r\\n\\t\\\\end\"");
    assert(escaped.size() >= 2);
    assert(escaped[0].kind == nudl::TokenKind::String);
    assert(escaped[0].text == std::string("line\r\n\t\\end"));

    std::cout << "smoke: PASS\n";
    return 0;
}
