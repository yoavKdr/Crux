#ifndef TOKEN_KIND_H
#define TOKEN_KIND_H

#include <string>
#include <iostream>

#include "tokens/token_type.h"

// ------------ Enum ------------
enum class TokenKind
{
    Error = 0,
    Assignment,
    Arithmetic,
    Relational,
    Gates,
    VariableType,
    Declaration,
    Data,
    Other
};

// ------------ Functions ------------
std::string to_string(TokenKind kind);

// ------------ Operators ------------
std::ostream& operator<<(std::ostream& os, TokenKind kind);

#endif // TOKEN_KIND_H
