#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "tokens/token.h"
#include "tokens/token_type.h"
#include "tokens/token_kind.h"

class Lexer
{
private:
    // --- Var ---
    std::unordered_map<TokenType, std::string> token_type_map;

    // --- Init ---
    static std::unordered_map<TokenType, std::string> token_map();

    // --- Detection functions ---
    static bool is_numeric(const std::string& s);
    static bool is_alphanumeric(const std::string& s);
    static bool is_alphanumeric_or_underscore(const std::string& s);
    static bool has_quotes(const std::string& s);

    // --- Private functions ---
    std::vector<std::string> split_from_operators(const std::string& source) const;

public:
    // --- Constructor ---
    Lexer();

    // --- control ---
    TokenType string_to_token_type(const std::string& value) const;
    std::string token_type_to_string(TokenType type) const;
    bool string_is_token_type(const std::string& value) const;
    static TokenKind token_type_to_kind(const TokenType& type);


    // --- Functions ---
    std::vector<Token> tokenization(const std::string& source) const;

    // --- Others ---
    static void print_tokens(const std::vector<Token>& tokens);
};

#endif // LEXER_H
