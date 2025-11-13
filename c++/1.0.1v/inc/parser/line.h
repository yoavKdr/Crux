#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>
#include <iostream>
#include "tokens/token.h"

class Line
{
private:
    std::vector<const Token*> tokens;
    int line_number;

public:
    // --- Constructors ---
    Line(int ln);

    // --- Getters & Setters ---
    const std::vector<const Token*>& get_tokens() const;
    int get_line_number() const;

    // --- Commands ---
    void add_token(const Token* token);

    bool empty() const;

    // --- Prints ---
    void print() const;
    void print_as_tokens() const;
    void point_at_token(const Token* token) const;
    void point_at_end() const;
    void print_error(const Token* token, const std::string& msg) const;
    void print_error(const std::string& msg) const;
};

#endif // LINE_H
