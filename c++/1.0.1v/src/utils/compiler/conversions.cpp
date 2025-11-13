#include "compiler/compiler.h"

// template <typename Target>
// Target clampCast(const Value& val)
// {
//     auto minVal = std::is_floating_point<Target>::value ?
//                   static_cast<Target>(std::numeric_limits<Target>::lowest()) :
//                   static_cast<Target>(std::numeric_limits<Target>::min());
//     auto maxVal = static_cast<Target>(std::numeric_limits<Target>::max());

//     return std::visit([&](auto&& v) -> Target {
//         return static_cast<Target>(std::clamp(v, minVal, maxVal));
//     }, val);

//     std::cout << "debug 2" << std::endl;
// }

// std::optional<Variable> ConvertVariableTo(const Variable& var, TokenType target)
// {
//     auto valOpt = var.getValue();
//     if (!valOpt) return std::nullopt;

//     const auto& val = *valOpt;

//     switch (target)
//     {
//         case TokenType::Int8:           return Variable(target, Value(clampCast<int8_t>(val)));
//         case TokenType::Int16:          return Variable(target, Value(clampCast<int16_t>(val)));
//         case TokenType::Int32:          return Variable(target, Value(clampCast<int32_t>(val)));
//         case TokenType::Int64:          return Variable(target, Value(clampCast<int64_t>(val)));
//         case TokenType::UnsignedInt8:   return Variable(target, Value(clampCast<uint8_t>(val)));
//         case TokenType::UnsignedInt16:  return Variable(target, Value(clampCast<uint16_t>(val)));
//         case TokenType::UnsignedInt32:  return Variable(target, Value(clampCast<uint32_t>(val)));
//         case TokenType::UnsignedInt64:  return Variable(target, Value(clampCast<uint64_t>(val)));
//         case TokenType::Float32:        return Variable(target, Value(clampCast<float>(val)));
//         case TokenType::Float64:        return Variable(target, Value(clampCast<double>(val)));
//         default:                        return std::nullopt;
//     }
// }

std::optional<Variable> StringToVariable(const std::string& str)
{
    try
    {
        // --- Floating-point numbers ---
        if (str.find('.') != std::string::npos)
        {
            double d = std::stod(str);
            return Variable(TokenType::Float64, d);
        }
        else
        {
            int64_t l = std::stoll(str);
            return Variable(TokenType::Int64, l);
        }
    }
    catch (const std::out_of_range&)
    {
        return std::nullopt;

    }
    catch (const std::invalid_argument&)
    {
        return std::nullopt; // not a number at all
    }
}