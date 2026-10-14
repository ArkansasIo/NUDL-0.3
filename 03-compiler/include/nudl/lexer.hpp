#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace nudl {
enum class TokenKind { Identifier, Number, String, Keyword, Symbol, End };
struct Token {
  TokenKind kind;
  std::string text;
  std::size_t line{};
  std::size_t column{};
};
std::vector<Token> lex(std::string_view source);
}
