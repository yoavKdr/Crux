#include "compiler/variable.h"

// --- Constructors ---
Variable::Variable(TokenType type) : type(type), value(std::nullopt) {}

Variable::Variable(TokenType type, const Value& val) : type(type), value(val) {}

// --- Getters & Setters ---
TokenType Variable::getType() const { return type; }
std::optional<Value> Variable::getValue() const { return value; }
void Variable::setValue(const Value& val) { value = val; }

bool Variable::hasValue() const { return value.has_value(); }

// --- premade values ---
Variable Variable::Empty() { return Variable(TokenType::Void); }