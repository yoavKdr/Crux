#ifndef ERROR_MSGS_H
#define ERROR_MSGS_H

#include <string>
#include "lexer.h"

class Errors
{
public:
    /// Lexer errors [001 - 3FF]
    static std::string e_001(const std::string& s); // [001] - unidentified charecter

    // Parser errors [400 - 7FF]
    static std::string e_400(const TokenType& expected, const TokenType& found); // [400] - unexpected token type
    static std::string e_400(const TokenKind& expected, const TokenType& found); // [400] - unexpected token type
    static std::string e_400(const std::vector<TokenType>& expected, const TokenType& found); // [400] - unexpected token type
    static std::string e_402(); // [402] - void var
    static std::string e_403(); // [403] - line without ending

    // Compiler errors [800 - BFF]
    static std::string e_800(const std::string& name); // [800] variable already exist
    static std::string e_801(const std::string& name); // [801] variable does not exist

    // Other errors [C00 - FFF]
    static std::string e_C00(); // [C00] - no lines

};

#endif // ERROR_MSGS_H
