#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <iostream>

#include "tokens/token_type.h"

// ---------- Utility ----------
inline void printIndent(int indent);
inline void printHeader(int indent, const std::string& name);

// ---------- Base AST Node ----------
enum class ASTType { NumberExpr, VariableExpr, BinaryExpr, VarDecl, AssignmentStmt };

struct ASTNode 
{
public:
    // --- Distructors ---
    virtual ~ASTNode() = default;
    
    // --- Commands ---
    virtual ASTType get_ast_type() const = 0;
    virtual void print(int indent = 0) const = 0;
};

// ---------- Expressions ----------
struct NumberExpr : ASTNode
{
private:
    // --- Vars ---
    std::string value;
public:
    // --- Constructors ---
    NumberExpr(const std::string& value);

    // --- Getters & Setters ---
    const std::string& get_value() const;

    // --- Commands ---
    ASTType get_ast_type() const override;
    void print(int indent = 0) const override;
};

struct VariableExpr : ASTNode
{
private:
    // --- Vars ---
    std::string name;

public:
    // --- Constructors ---
    VariableExpr(const std::string& name);

    // --- Getters & Setters ---
    const std::string& get_name() const;

    // --- Commands ---
    ASTType get_ast_type() const override;
    void print(int indent = 0) const override;
};

struct BinaryExpr : ASTNode
{
private:
    // --- Vars ---
    TokenType aritOp;
    std::unique_ptr<ASTNode> left, right;

public:
    // --- Constructors ---
    BinaryExpr(TokenType aritOp, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);

    // --- Getters & Setters ---
    TokenType get_op() const;
    const ASTNode* get_left() const;
    const ASTNode* get_right() const;

    // --- Commands ---
    ASTType get_ast_type() const override;
    void print(int indent = 0) const override;
};

// ---------- Declarations ----------
struct VarDecl : ASTNode
{
private:
    // --- Vars ---
    TokenType type;
    std::string name;
    std::unique_ptr<ASTNode> initExpr;

public:
    // --- Constructors ---
    VarDecl(TokenType type, const std::string& name, std::unique_ptr<ASTNode> initExpr);

    // --- Getters & Setters ---
    const ASTNode* get_init_expr() const;
    TokenType get_type() const;
    const std::string& get_name() const;

    // --- Commands ---
    ASTType get_ast_type() const override;
    void print(int indent = 0) const override;
};

// ---------- Statements ----------
struct AssignmentStmt : ASTNode
{
private:
    // --- Vars ---
    TokenType assiOp;
    std::string name;
    std::unique_ptr<ASTNode> expr;

public:
    // --- Constructors ---
    AssignmentStmt(TokenType assiOp, const std::string& name, std::unique_ptr<ASTNode> expr);

    // --- Getters & Setters ---
    TokenType get_op() const;
    const std::string& get_name() const;
    const ASTNode* get_expr() const;

    // --- Commands ---
    ASTType get_ast_type() const override;
    void print(int indent = 0) const override;
};

#endif // AST_H