#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <string>

#include "parser/ast.h"
#include "parser/line.h"
#include "error_msgs.h"
#include "lexer.h"

class Parser 
{
private:
    // --- Vars ---
    std::vector<Token> tokens_storage;
    std::vector<Line> lines;

    uint64_t line_pos;
    uint64_t token_pos;

    uint64_t lexer_errors;
    uint64_t parser_errors;
    uint64_t other_errors;

    // --- Control functions ---
    const Token* current() const;
    bool line_ended();
    void next_token();
    void back_token();
    void next_line();

    // --- Print functions ---
    void print_status();

    // --- Functions ---
    std::vector<Line> split_tokens_to_lines(const std::vector<Token>& tokens);

    // --- Parsing functions ---
    std::unique_ptr<ASTNode> parseFactor();             // numbers, variables, parentheses
    std::unique_ptr<ASTNode> parseLowExpression();      // handles lowest-precedence (+, -)
    std::unique_ptr<ASTNode> parseMediumExpression();   // handles medium-precedence (*, /, %)
    std::unique_ptr<ASTNode> parseVarDecl();            // variable declarations
    std::unique_ptr<ASTNode> parseAssignmentStmt();     // Assignment Stmt

public:
    // --- Constructor ---
    Parser(const std::vector<Token>& tokens);

    // --- Functions ---
    std::vector<std::unique_ptr<ASTNode>> parse();
};

#endif // PARSER_H