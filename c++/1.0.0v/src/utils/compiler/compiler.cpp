#include "compiler/compiler.h"
#include <iostream>

// --- Constructor ---
Compiler::Compiler() = default;

// --- AST Solvers Functions ---
void Compiler::VarDeclSolver(const VarDecl* ast)
{
    if (symbols.exists(ast->get_name()))
    {
        std::string msg = Errors::e_800(ast->get_name());
        std::cout << msg << std::endl;
        ++compiler_errors;
        return;
    }

    std::optional<Variable> var = AstExprSolver(ast->get_init_expr());
    if (var)
    {
        //var = ConvertVariableTo(var.value(), ast->get_type());

        if (!var)
        {
            // error: var cant be varDecl.type
            return;
        }
    }

    symbols.declare(ast->get_name(), var.value());
}
void Compiler::AssignmentStmtSolver(const AssignmentStmt* ast)
{
    std::optional<Variable> var = symbols.getVar(ast->get_name());
    if (!var)
    {
        std::string msg = Errors::e_801(ast->get_name());
        std::cout << msg << std::endl;
        ++compiler_errors;
    }
    TokenType var_tt = var->getType();


    std::optional<Variable> newVar = AstExprSolver(ast->get_expr());
    if (!newVar)
    {
        // invalid expr
    }
    
    TokenType operation = TokenType::Assign;
    switch (ast->get_op())
    {
        case TokenType::PlusAssign : operation = TokenType::Plus; break;
        case TokenType::MinusAssign : operation = TokenType::Minus; break;
        case TokenType::MultiplyAssign : operation = TokenType::Multiply; break;
        case TokenType::DivideAssign : operation = TokenType::Divide; break;
        case TokenType::ModulusAssign : operation = TokenType::Modulus; break;                
        default: operation = TokenType::Void; break;
    }
    
    if (operation == TokenType::Void)
    {
        // invalid
    }
    else if (operation != TokenType::Assign)
    {
        //std::optional<Variable> tempVar = ConvertVariableTo(var.value(), newVar->getType());
        //if (!tempVar)
        //{
            // cant convert;
        //}

        newVar = BinaryExprSolver(var.value(), newVar.value(), operation);
    }

    //newVar = ConvertVariableTo(newVar.value(), var_tt);

    //if (newVar)
    //{
        // error: var cant be varDecl.type
    //}
    symbols.setValue(ast->get_name(), newVar->getValue().value());
}

std::optional<Variable> Compiler::AstExprSolver(const ASTNode* expr)
{
    if (!expr) 
        return std::nullopt; // Expression pointer is null → nothing to evaluate, invalid AST node.

    switch (expr->get_ast_type())
    {
        case ASTType::NumberExpr:
        {
            const NumberExpr* numExpr = static_cast<const NumberExpr*>(expr);
            return StringToVariable(numExpr->get_value());
        }

        case ASTType::VariableExpr:
        {
            const VariableExpr* varExpr = static_cast<const VariableExpr*>(expr);

            if (!symbols.exists(varExpr->get_name()))
            {
                return std::nullopt; // Variable not declared → undefined variable error.
            }

            std::optional<Variable> var = symbols.getVar(varExpr->get_name());

            if (!var.has_value())
            {
                return std::nullopt; // Variable exists but has no value → uninitialized variable error.
            }

            return var;
        }

        case ASTType::BinaryExpr:
        {
            const BinaryExpr* binExpr = static_cast<const BinaryExpr*>(expr);

            std::optional<Variable> left = AstExprSolver(binExpr->get_left());
            std::optional<Variable> right = AstExprSolver(binExpr->get_right());

            if (!left)
            {
                return std::nullopt; // Left operand failed to evaluate → invalid sub-expression.
            }
            if (!right)
            {
                return std::nullopt; // Right operand failed to evaluate → invalid sub-expression.
            }

            return BinaryExprSolver(left.value(), right.value(), binExpr->get_op());
        }

        default:
            return std::nullopt; // Unknown AST type → syntax error or incomplete implementation
    }
}

std::optional<Variable> Compiler::BinaryExprSolver(const Variable& left, const Variable& right, TokenType op)
{
    if (left.getType() == right.getType() && left.getType() == TokenType::Int64)
    {
        int64_t a = std::get<int64_t>(*left.getValue());
        int64_t b = std::get<int64_t>(*right.getValue());

        switch (op)
        {
            case TokenType::Plus:     return Variable(TokenType::Int64, a + b);
            case TokenType::Minus:    return Variable(TokenType::Int64, a - b);
            case TokenType::Multiply: return Variable(TokenType::Int64, a * b);
            case TokenType::Divide:   return Variable(TokenType::Int64, a / b);
            case TokenType::Modulus:  return Variable(TokenType::Int64, a % b);
            default: std::nullopt;
        }
    }
    else
    {
        double a = left.getType() == TokenType::Int64
            ? static_cast<double>(std::get<int64_t>(*left.getValue()))
            : std::get<double>(*left.getValue());
        double b = right.getType() == TokenType::Int64
            ? static_cast<double>(std::get<int64_t>(*right.getValue()))
            : std::get<double>(*right.getValue());

        switch (op)
        {
            case TokenType::Plus:     return Variable(TokenType::Float64, a + b);
            case TokenType::Minus:    return Variable(TokenType::Float64, a - b);
            case TokenType::Multiply: return Variable(TokenType::Float64, a * b);
            case TokenType::Divide:   return Variable(TokenType::Float64, a / b);
            case TokenType::Modulus:  std::nullopt; // Modulo not supported for floats
            default: std::nullopt;
        }
    }

    return std::nullopt;
}

// --- Functions ---
void Compiler::compile(const std::vector<std::unique_ptr<ASTNode>>& asts)
{
    compiler_errors = 0;
    
    for (int i = 0; i < asts.size(); ++i)
    {
        switch (asts[i]->get_ast_type())
        {
            case ASTType::VarDecl:
            {
                VarDeclSolver(static_cast<VarDecl*>(asts[i].get()));
                break;
            }

            case ASTType::AssignmentStmt:
            {
                AssignmentStmtSolver(static_cast<AssignmentStmt*>(asts[i].get()));
                break;
            }

            default:
                break;
        }
    }
}

// --- Getters ---
const SymbolTable& Compiler::getSymbolTable() const
{
    return symbols;
}

// --- Prints ---
void Compiler::printSymbols() const
{
    std::cout << "=== Symbol Table ===" << std::endl;
    symbols.printAll();
}
