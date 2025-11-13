#include "tokens/token.h"

// --- Constructor ---
Token::Token(const std::string& value, TokenType type)
{
    token_value = value;
    token_type = type;
}
Token::Token()
{
    token_value = "";
    token_type = TokenType::Empty;
}

// --- Getters ---
TokenType Token::get_token_type() const
{
    return token_type;
}
const std::string& Token::get_token_value() const
{
    return token_value;
}

// --- Setters ---
void Token::set_token_type(TokenType type)
{
    token_type = type;
}
void Token::set_token_value(const std::string& value)
{
    token_value = value;
}

// --- Premade values ---
Token Token::Empty()
{
    return Token("", TokenType::Empty);
}

// --- Commands ---
void Token::print() const
{
    std::cout << "Token: " << token_value
              << " | Type: " << token_type
              << std::endl;
}
