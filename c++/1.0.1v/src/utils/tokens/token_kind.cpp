#include "tokens/token_kind.h"

// ------------ Functions ------------
std::string to_string(TokenKind kind)
{
    switch (kind)
    {
        case TokenKind::Error:        return "Error";
        case TokenKind::Assignment:   return "Assignment";
        case TokenKind::Arithmetic:   return "Arithmetic";
        case TokenKind::Relational:   return "Relational";
        case TokenKind::Gates:        return "Gates";
        case TokenKind::VariableType: return "VariableType";
        case TokenKind::Declaration:  return "Declaration";
        case TokenKind::Data:         return "Data";
        case TokenKind::Other:        return "Other";
        default:                      return "Error";
    }
}

// ------------ Operators ------------
std::ostream& operator<<(std::ostream& os, TokenKind kind)
{
    return os << to_string(kind);
}
