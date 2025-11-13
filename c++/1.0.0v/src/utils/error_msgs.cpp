#include "error_msgs.h"

#include <string>

// ---------------- Lexer Errors ----------------
std::string Errors::e_001(const std::string& s)
{
    return std::string("Lexer Error [001]: unidentified value \"") + s + "\".";
}


// ---------------- Parser Errors ----------------
std::string Errors::e_400(const TokenType& expected, const TokenType& found)
{
    std::string msg = "Parser Error [400]: unexpected token has been found.";
    msg += "\n\tExpected type: " + to_string(expected);
    msg += "\n\tfound: " + to_string(found);
    return msg;
}
std::string Errors::e_400(const TokenKind& expected, const TokenType& found)
{
    std::string msg = "Parser Error [400]: unexpected token has been found.";
    msg += "\n\tExpected kind: " + to_string(expected);
    msg += "\n\tfound: " + to_string(found);
    return msg;
}
std::string Errors::e_400(const std::vector<TokenType>& expected, const TokenType& found)
{
    std::string msg = "Parser Error [400]: unexpected token has been found.";
    msg += "\n\tExpected types:";
    for(int i = 0; i < expected.size(); ++i)
    {
        msg += "\n\t\t" + to_string(expected[i]);
    }
    msg += "\n\tfound: " + to_string(found);
    return msg;
}
std::string Errors::e_402()
{
    std::string msg = "Parser Error [402]: \"void\" is not a valid var type.";
    return msg;
}
std::string Errors::e_403()
{
    std::string msg = "Parser Error [403]: the line ended without \';\'.";
    return msg;
}

// ---------------- Compiler Errors ----------------
std::string Errors::e_800(const std::string& name)
{
    return "Compiler Error [800]: variable \"" + name + "\" already exist";
}
std::string Errors::e_801(const std::string& name)
{
    return "Compiler Error [801]: variable \"" + name + "\" does not exist";
}

// ---------------- Other Errors ----------------
std::string Errors::e_C00()
{
    std::string msg = "Parser Error [e_C00]: an dataless/empty file has been given.";
    return msg;
}