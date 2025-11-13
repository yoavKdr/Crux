#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <variant>
#include <optional>
#include "tokens/token_type.h"

using Value = std::variant<
    int8_t,   // i8
    int16_t,  // i16
    int32_t,  // i32
    int64_t,  // i64
    uint8_t,  // u8
    uint16_t, // u16
    uint32_t, // u32
    uint64_t, // u64
    float,    // f32
    double,   // f64
    char,     // char
    std::string, // string
    bool      // bool
>;

class Variable
{
private:
    // --- Vars ---
    TokenType type;
    std::optional<Value> value;

public:
    // --- Constructors ---
    Variable(TokenType type);
    Variable(TokenType type, const Value& val);

    // --- Getters & Setters ---
    TokenType getType() const;
    std::optional<Value> getValue() const;
    void setValue(const Value& val);

    bool hasValue() const;

    // --- premade values ---
    Variable Empty();
};

#endif // VARIABLE_H
