#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

#include "tokens/token_type.h"
#include "tokens/token_kind.h"

class Token
{
private:
    // --- Vars ---
    TokenType token_type;
    std::string token_value;

public:
    // --- Constructors ---
    Token(const std::string& value, TokenType type);
    Token();

    // --- Getters & Setters ---
    TokenType get_token_type() const;
    const std::string& get_token_value() const;

    void set_token_type(TokenType type);
    void set_token_value(const std::string& value);

    // --- Premade values ---
    static Token Empty();

    // --- Commands ---
    void print() const;
};

#endif // TOKEN_H
