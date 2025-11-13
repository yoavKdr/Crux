#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>
#include <iostream>

// ------------ Enum ------------
enum class TokenType
{
    // ------------ Errors ------------
    Empty,
    Unknown,
    Syntax,

    // ------------ Assignment Operators ------------
    ASSP,
    Assign,
    PlusAssign,
    MinusAssign,
    MultiplyAssign,
    DivideAssign,
    ModulusAssign,
    ASEP,

    // ------------ Arithmetic Operators ------------
    ARSP,
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulus,
    AREP,

    // ------------ Relational Operators ------------
    RSP,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    Equal,
    NotEqual,
    REP,

    // ------------ Gates Operators ------------
    GSP,
    And,
    Or,
    Not,
    GEP,

    // ------------ Variable Types ------------
    VTSP,
    Int8,
    Int16,
    Int32,
    Int64,
    UnsignedInt8,
    UnsignedInt16,
    UnsignedInt32,
    UnsignedInt64,
    Float32,
    Float64,
    Char,
    String,
    Bool,
    Any,
    Void,
    VTEP,

    // ------------ Declarations ------------
    DESP,
    VariableDeclaration,
    FunctionDeclaration,
    DEEP,

    // ------------ Data ------------
    DASP,
    Alphanumeric,
    Numeric,
    Text,
    DAEP,

    // ------------ Other ------------
    OSP,
    Comment,
    Colon,
    SemiColon,
    Dot,
    Comma,
    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    OpenBracket,
    CloseBracket,
    OEP
};

// ------------ Functions ------------
std::string to_string(TokenType type);

// ------------ Operators ------------
std::ostream& operator<<(std::ostream& os, TokenType type);

#endif // TOKEN_TYPE_H
