#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <cmath>

#include "parser/ast.h"
#include "error_msgs.h"
#include "compiler/symbol_table.h"
#include "compiler/conversions.h"

class Compiler
{
private:
    // --- vars ---
    SymbolTable symbols;
    uint64_t compiler_errors;

    // --- AST Solvers Functions ---
    void VarDeclSolver(const VarDecl* ast);
    void AssignmentStmtSolver(const AssignmentStmt* ast);
    std::optional<Variable> AstExprSolver(const ASTNode* expr);
    std::optional<Variable> BinaryExprSolver(const Variable& left, const Variable& right, TokenType op);

public:
    // --- Constructors ---
    Compiler();

    // --- Functions ---
    void compile(const std::vector<std::unique_ptr<ASTNode>>& asts);

    // --- Getters ---
    const SymbolTable& getSymbolTable() const;

    // --- Prints ---
    void printSymbols() const;
};

#endif // COMPILER_H
