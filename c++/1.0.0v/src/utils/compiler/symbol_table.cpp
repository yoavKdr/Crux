#include "compiler/symbol_table.h"
#include <iostream>

SymbolTable::SymbolTable() = default;

// --- Declare Variable ---
bool SymbolTable::declare(const std::string& name, const Variable& var)
{
    if (table.find(name) != table.end())
        return false; // already exists

    table.emplace(name, var);
    return true;
}

// --- Set Variable Value ---
bool SymbolTable::setValue(const std::string& name, const Value& val)
{
    auto it = table.find(name);
    if (it == table.end()) return false;

    it->second.setValue(val);
    return true;
}

// --- Get Variable ---
std::optional<Variable> SymbolTable::getVar(const std::string& name) const
{
    auto it = table.find(name);
    if (it == table.end()) return std::nullopt;
    return it->second;
}

// --- Exists ---
bool SymbolTable::exists(const std::string& name) const
{
    return table.find(name) != table.end();
}

// --- Print all ---
void SymbolTable::printAll() const
{
    for (const auto& [name, var] : table) {
        std::cout << "Variable: " << name << " | Type: " << var.getType() << " | Value: ";
        if (!var.hasValue()) std::cout << "null";
        else std::visit([](auto&& val){ std::cout << val; }, var.getValue().value());
        std::cout << "\n";
    }
}
