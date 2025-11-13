#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <optional>
#include "variable.h"

class SymbolTable
{
private:
    // --- Vars ---
    std::unordered_map<std::string, Variable> table;

public:
    // --- Constructors ---
    SymbolTable();

    // --- Add / Declare Variable ---
    bool declare(const std::string& name, const Variable& var);

    // --- Set Variable Value ---
    bool setValue(const std::string& name, const Value& val);

    // --- Get Variable ---
    std::optional<Variable> getVar(const std::string& name) const;

    // --- Check if exists ---
    bool exists(const std::string& name) const;

    // --- Print all ---
    void printAll() const;
};

#endif // SYMBOL_TABLE_H
