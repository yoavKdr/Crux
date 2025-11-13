#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <optional>
#include <type_traits>
#include <limits>
#include <algorithm>

#include "tokens/token_type.h"
#include "compiler/variable.h"
#include "error_msgs.h"

// --- math helper functions ---
template <typename Target>
Target clampCast(const Value& val);
std::optional<Variable> ConvertVariableTo(const Variable& var, TokenType target);
std::optional<Variable> StringToVariable(const std::string& str);



#endif // CONVERSIONS_H