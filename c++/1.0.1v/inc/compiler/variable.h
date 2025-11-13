#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <variant>
#include <optional>
#include "tokens/token_type.h"

template <typename T>
class Variable
{
private:
    // --- Vars ---
    TokenType type;
    std::optional<T> value;

public:
    // --- Constructors ---
    Variable(TokenType type);
    Variable(TokenType type, const T& val);

    // --- Getters & Setters ---
    TokenType getType() const;
    std::optional<T> getValue() const;
    void setValue(const T& val);

    bool hasValue() const;

    // --- premade values ---
    Variable Empty();
};

#endif // VARIABLE_H
