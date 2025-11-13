#include "tokens/token_type.h"

// ------------ Functions ------------
std::string to_string(TokenType type)
{
    switch (type)
    {
        // ------------ Error ------------
        case TokenType::Empty: return "Empty";
        case TokenType::Unknown: return "Unknown";
        case TokenType::Syntax: return "Syntax";

        // ------------ Assignment Operators ------------
        case TokenType::Assign: return "Assign";
        case TokenType::PlusAssign: return "PlusAssign";
        case TokenType::MinusAssign: return "MinusAssign";
        case TokenType::MultiplyAssign: return "MultiplyAssign";
        case TokenType::DivideAssign: return "DivideAssign";
        case TokenType::ModulusAssign: return "ModulusAssign";

        // ------------ Arithmetic Operators ------------
        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Multiply: return "Multiply";
        case TokenType::Divide: return "Divide";
        case TokenType::Modulus: return "Modulus";

        // ------------ Relational Operators ------------
        case TokenType::Less: return "Less";
        case TokenType::Greater: return "Greater";
        case TokenType::LessEqual: return "LessEqual";
        case TokenType::GreaterEqual: return "GreaterEqual";
        case TokenType::Equal: return "Equal";
        case TokenType::NotEqual: return "NotEqual";

        // ------------ Gates Operators ------------
        case TokenType::And: return "And";
        case TokenType::Or: return "Or";
        case TokenType::Not: return "Not";

        // ------------ Variable Types ------------
        case TokenType::Int8: return "Int8";
        case TokenType::Int16: return "Int16";
        case TokenType::Int32: return "Int32";
        case TokenType::Int64: return "Int64";
        case TokenType::UnsignedInt8: return "UnsignedInt8";
        case TokenType::UnsignedInt16: return "UnsignedInt16";
        case TokenType::UnsignedInt32: return "UnsignedInt32";
        case TokenType::UnsignedInt64: return "UnsignedInt64";
        case TokenType::Float32: return "Float32";
        case TokenType::Float64: return "Float64";
        case TokenType::Char: return "Char";
        case TokenType::String: return "String";
        case TokenType::Bool: return "Bool";
        case TokenType::Any: return "Any";
        case TokenType::Void: return "Void";

        // ------------ Declarations ------------
        case TokenType::VariableDeclaration: return "NewVariable";
        case TokenType::FunctionDeclaration: return "NewFunction";

        // ------------ Data ------------
        case TokenType::Alphanumeric: return "Alphanumeric";
        case TokenType::Numeric: return "Numeric";
        case TokenType::Text: return "Text";

        // ------------ Other ------------
        case TokenType::Comment: return "Comment";
        case TokenType::Colon: return "Colon";
        case TokenType::SemiColon: return "SemiColon";
        case TokenType::Dot: return "Dot";
        case TokenType::Comma: return "Comma";
        case TokenType::OpenParen: return "OpenParen";
        case TokenType::CloseParen: return "CloseParen";
        case TokenType::OpenBrace: return "OpenBrace";
        case TokenType::CloseBrace: return "CloseBrace";
        case TokenType::OpenBracket: return "OpenBracket";
        case TokenType::CloseBracket: return "CloseBracket";

        default: return "Unknown";
    }
}

// ------------ Operators ------------
std::ostream& operator<<(std::ostream& os, TokenType type)
{
    return os << to_string(type);
}
