#include "parser/line.h"

// --- Constructors ---
Line::Line(int ln) : line_number(ln) {}

// --- Getters ---
const std::vector<const Token*>& Line::get_tokens() const
{
    return tokens;
}

int Line::get_line_number() const
{
    return line_number;
}

// --- Commands ---
void Line::add_token(const Token* token)
{
    tokens.push_back(token);
}

bool Line::empty() const
{
    return tokens.empty();
}

// --- Prints ---
void Line::print() const
{
    for (const Token* token : tokens)
    {
        std::cout << token->get_token_value() << " ";
    }
    std::cout << "\n";
}

void Line::print_as_tokens() const
{
    for (const Token* token : tokens)
    {
        token->print();
    }
}

void Line::point_at_token(const Token* token) const
{
    for (const Token* t : tokens)
    {
        const std::string& val = t->get_token_value();
        if (t == token)
        {
            for (size_t i = 0; i < val.size(); ++i) std::cout << "^";
        }
        else
        {
            for (size_t i = 0; i < val.size(); ++i) std::cout << "-";
        }
        std::cout << "-";
    }
    std::cout << "\n";
}
void Line::point_at_end() const
{
    for (const Token* t : tokens)
    {
        const std::string& val = t->get_token_value();
        for (size_t i = 0; i < val.size(); ++i) std::cout << "-";
        std::cout << "-";
    }
    std::cout << "^";
    std::cout << "\n";
}

void Line::print_error(const Token* token, const std::string& msg) const
{
    std::cout << "[Ln." << line_number << "]" << std::endl;
    print();
    point_at_token(token);
    std::cout << msg << "\n";
}
void Line::print_error(const std::string& msg) const
{
    std::cout << "[Ln." << line_number << "]" << std::endl;
    print();
    point_at_end();
    std::cout << msg << "\n";
}
