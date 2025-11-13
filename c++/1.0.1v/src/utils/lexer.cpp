#include <cctype>
#include <sstream>
#include <algorithm>

#include "lexer.h"

// --- Constructor ---
Lexer::Lexer()
{
    token_type_map = token_map();
}

// --- Init ---
std::unordered_map<TokenType, std::string> Lexer::token_map()
{
    std::unordered_map<TokenType, std::string> map;

    // ------------ Errors ------------
    map[TokenType::Empty] = "";

    // Assignment
    map[TokenType::Assign] = "=";
    map[TokenType::PlusAssign] = "+=";
    map[TokenType::MinusAssign] = "-=";
    map[TokenType::MultiplyAssign] = "*=";
    map[TokenType::DivideAssign] = "/=";
    map[TokenType::ModulusAssign] = "%=";

    // Arithmetic
    map[TokenType::Plus] = "+";
    map[TokenType::Minus] = "-";
    map[TokenType::Multiply] = "*";
    map[TokenType::Divide] = "/";
    map[TokenType::Modulus] = "%";

    // Relational
    map[TokenType::Less] = "<";
    map[TokenType::Greater] = ">";
    map[TokenType::LessEqual] = "<=";
    map[TokenType::GreaterEqual] = ">=";
    map[TokenType::Equal] = "==";
    map[TokenType::NotEqual] = "!=";

    // Gates
    map[TokenType::And] = "&&";
    map[TokenType::Or] = "||";
    map[TokenType::Not] = "!";

    // VariableTypes
    map[TokenType::Int8] = "i8";
    map[TokenType::Int16] = "i16";
    map[TokenType::Int32] = "i32";
    map[TokenType::Int64] = "i64";
    map[TokenType::UnsignedInt8] = "u8";
    map[TokenType::UnsignedInt16] = "u16";
    map[TokenType::UnsignedInt32] = "u32";
    map[TokenType::UnsignedInt64] = "u64";
    map[TokenType::Float32] = "f32";
    map[TokenType::Float64] = "f64";
    map[TokenType::Char] = "char";
    map[TokenType::String] = "string";
    map[TokenType::Bool] = "bool";
    map[TokenType::Any] = "any";
    map[TokenType::Void] = "void";

    // Declarations
    map[TokenType::VariableDeclaration] = "var";
    map[TokenType::FunctionDeclaration] = "func";

    // Other
    map[TokenType::SemiColon] = ";";
    map[TokenType::Comment] = "//";
    map[TokenType::Dot] = ".";
    map[TokenType::Comma] = ",";
    map[TokenType::Colon] = ":";
    map[TokenType::OpenParen] = "(";
    map[TokenType::CloseParen] = ")";
    map[TokenType::OpenBrace] = "{";
    map[TokenType::CloseBrace] = "}";
    map[TokenType::OpenBracket] = "[";
    map[TokenType::CloseBracket] = "]";

    return map;
}

// --- Detection functions ---
bool Lexer::is_numeric(const std::string& s)
{
    std::istringstream iss(s);
    double f;
    return (iss >> f) && (iss.eof());
}

bool Lexer::is_alphanumeric(const std::string& s)
{
    return std::all_of(s.begin(), s.end(), [](char c){ return std::isalnum(c); });
}

bool Lexer::is_alphanumeric_or_underscore(const std::string& s)
{
    return std::all_of(s.begin(), s.end(), [](char c){ return std::isalnum(c) || c == '_'; });
}

bool Lexer::has_quotes(const std::string& s)
{
    return s.size() > 1 && s.front() == '"' && s.back() == '"';
}

// --- Map control ---
TokenType Lexer::string_to_token_type(const std::string& value) const
{
    for (const std::pair<const TokenType, std::string>& pair : token_type_map)
    {
        if (pair.second == value)
            return pair.first;
    }

    if (has_quotes(value))
        return TokenType::Text;

    if (is_numeric(value))
        return TokenType::Numeric;

    if (is_alphanumeric_or_underscore(value))
        return TokenType::Alphanumeric;

    return TokenType::Unknown;
}

std::string Lexer::token_type_to_string(TokenType type) const
{
    std::unordered_map<TokenType, std::string>::const_iterator it = token_type_map.find(type);
    if (it != token_type_map.end())
        return it->second;
    return "";
}

bool Lexer::string_is_token_type(const std::string& value) const
{
    return string_to_token_type(value) != TokenType::Unknown;
}

TokenKind Lexer::token_type_to_kind(const TokenType& type)
{
    int v = static_cast<int>(type);

    if (v >= static_cast<int>(TokenType::ASSP) && v <= static_cast<int>(TokenType::ASEP))
        return TokenKind::Assignment;

    if (v >= static_cast<int>(TokenType::ARSP) && v <= static_cast<int>(TokenType::AREP))
        return TokenKind::Arithmetic;

    if (v >= static_cast<int>(TokenType::RSP) && v <= static_cast<int>(TokenType::REP))
        return TokenKind::Relational;

    if (v >= static_cast<int>(TokenType::GSP) && v <= static_cast<int>(TokenType::GEP))
        return TokenKind::Gates;

    if (v >= static_cast<int>(TokenType::VTSP) && v <= static_cast<int>(TokenType::VTEP))
        return TokenKind::VariableType;

    if (v >= static_cast<int>(TokenType::DESP) && v <= static_cast<int>(TokenType::DEEP))
        return TokenKind::Declaration;

    if (v >= static_cast<int>(TokenType::DASP) && v <= static_cast<int>(TokenType::DAEP))
        return TokenKind::Data;

    if (v >= static_cast<int>(TokenType::OSP) && v <= static_cast<int>(TokenType::OEP))
        return TokenKind::Other;

    return TokenKind::Error;
}

// --- Split from operators ---
std::vector<std::string> Lexer::split_from_operators(const std::string& source) const
{
    std::vector<std::string> results;
    size_t start_index = 0;

    for (size_t location = 0; location < source.size(); ++location)
    {
        std::string new_word = source.substr(start_index, location - start_index + 1);
        if (string_is_token_type(new_word))
        {
            if (location + 1 >= source.size() || 
                !string_is_token_type(new_word + source[location + 1]))
            {
                results.push_back(new_word);
                start_index = location + 1;
            }
        }
        else if (location + 1 >= source.size())
        {
            results.push_back(new_word);
        }
    }

    return results;
}

// --- Tokenization ---
std::vector<Token> Lexer::tokenization(const std::string& source) const
{
    std::vector<Token> tokens;
    std::istringstream iss(source);
    std::string word;

    while (iss >> word)
    {
        TokenType tt = string_to_token_type(word);

        if (tt != TokenType::Unknown)
        {
            tokens.push_back(Token(word, tt));
            continue;
        }

        for (std::string& new_word : split_from_operators(word))
        {
            tt = string_to_token_type(new_word);
            if (tt == TokenType::Unknown)
                tt = TokenType::Syntax;
            tokens.push_back(Token(new_word, tt));
        }
    }

    return tokens;
}

// --- Print tokens ---
void Lexer::print_tokens(const std::vector<Token>& tokens)
{
    for (const Token& token : tokens)
        token.print();
}
