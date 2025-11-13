#include "parser/ast.h"

// ---------- Utility ----------
inline void printIndent(int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << (i % 2 == 0 ? '-' : ' ');
    }
    std::cout << "| ";
}
inline void printHeader(int indent, const std::string& name)
{
    printIndent(indent);
    std::cout << "[" << name << "]\n";
}

// ---------- NumberExpr ----------
NumberExpr::NumberExpr(const std::string& value) : value(value) {}

const std::string& NumberExpr::get_value() const 
{
    return value;
}

ASTType NumberExpr::get_ast_type() const { return ASTType::NumberExpr; }

void NumberExpr::print(int indent) const 
{
    printIndent(indent);
    std::cout << "Number: " << value << "\n";
}

// ---------- VariableExpr ----------
VariableExpr::VariableExpr(const std::string& name) : name(name) {}

const std::string& VariableExpr::get_name() const 
{
    return name;
}

ASTType VariableExpr::get_ast_type() const { return ASTType::VariableExpr; }

void VariableExpr::print(int indent) const 
{
    printIndent(indent);
    std::cout << "Variable: " << name << "\n";
}

// ---------- BinaryExpr ----------
BinaryExpr::BinaryExpr(TokenType aritOp, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : aritOp(aritOp), left(std::move(left)), right(std::move(right)) {}

TokenType BinaryExpr::get_op() const 
{
    return aritOp;
}

const ASTNode* BinaryExpr::get_left() const 
{
    return left.get();
}

const ASTNode* BinaryExpr::get_right() const 
{
    return right.get();
}

ASTType BinaryExpr::get_ast_type() const { return ASTType::BinaryExpr; }

void BinaryExpr::print(int indent) const 
{
    printHeader(indent, "BinaryExpr");

    printIndent(indent + 2);
    std::cout << "Operator: " << aritOp << "\n";

    printHeader(indent + 2, "Left");
    if (left) left->print(indent + 4);

    printHeader(indent + 2, "Right");
    if (right) right->print(indent + 4);
}

// ---------- VarDecl ----------
VarDecl::VarDecl(TokenType type, const std::string& name, std::unique_ptr<ASTNode> initExpr)
    : type(type), name(name), initExpr(std::move(initExpr)) {}

const ASTNode* VarDecl::get_init_expr() const 
{
    return initExpr.get();
}

TokenType VarDecl::get_type() const 
{
    return type;
}

const std::string& VarDecl::get_name() const 
{
    return name;
}

ASTType VarDecl::get_ast_type() const { return ASTType::VarDecl; }

void VarDecl::print(int indent) const 
{
    printHeader(indent, "VarDecl");

    printIndent(indent + 2);
    std::cout << "Name: " << name << "\n";

    printIndent(indent + 2);
    std::cout << "Type: " << type << "\n";

    printHeader(indent + 2, "Initializer");
    if (initExpr)
    {
        initExpr->print(indent + 4);
    }
}

// ---------- AssignmentStmt ----------
AssignmentStmt::AssignmentStmt(TokenType assiOp, const std::string& name, std::unique_ptr<ASTNode> expr)
    : assiOp(assiOp), name(name), expr(std::move(expr)) {}

TokenType AssignmentStmt::get_op() const 
{
    return assiOp;
}

const std::string& AssignmentStmt::get_name() const 
{
    return name;
}

const ASTNode* AssignmentStmt::get_expr() const 
{
    return expr.get();
}

ASTType AssignmentStmt::get_ast_type() const { return ASTType::AssignmentStmt; }

void AssignmentStmt::print(int indent) const 
{
    printHeader(indent, "AssignmentStmt");

    printIndent(indent + 2);
    std::cout << "Name: " << name << "\n";

    printIndent(indent + 2);
    std::cout << "Assignment Type: " << assiOp << "\n";

    printHeader(indent + 2, "Expreation");
    if (expr)
    {
        expr->print(indent + 4);
    }
}
