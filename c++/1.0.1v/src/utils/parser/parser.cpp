#include "parser/parser.h"

#include <stdexcept>
#include <iostream>

// --- Constructor ---
Parser::Parser(const std::vector<Token>& tokens)
{
    tokens_storage = tokens;
    lines = Parser::split_tokens_to_lines(tokens_storage);

    line_pos = 0;
    token_pos = 0;
    lexer_errors = 0;
    parser_errors = 0;
    other_errors = 0;
}

// --- Constrol functions ---
const Token* Parser::current() const
{
    return lines[line_pos].get_tokens()[token_pos];
}
bool Parser::line_ended()
{
    return token_pos == lines[line_pos].get_tokens().size() - 1;
}
void Parser::next_token()
{
    if (token_pos < lines[line_pos].get_tokens().size() - 1)
    {
        ++token_pos;
    }
}
void Parser::back_token()
{
    if (token_pos > 0)
    {
        --token_pos;
    }
}
void Parser::next_line()
{
    if (line_pos < lines.size() - 1)
    {
        ++line_pos;
        token_pos = 0;
    }
}

// --- Print functions ---
void Parser::print_status()
{
    std::cout << "[Status]" << std::endl;
    std::cout << "  Lines of code: " << lines.size() << std::endl;

    if (lexer_errors != 0)
    {
        std::cout << "  Lexer errors: " << lexer_errors << std::endl;
    }
    else
    {
        std::cout << "  Parser errors: " << parser_errors << std::endl;
    }

    std::cout << "  Other errors: " << other_errors << std::endl;
}

// --- Functions ---
std::vector<Line> Parser::split_tokens_to_lines(const std::vector<Token>& tokens)
{
    std::vector<Line> lines;
    int current_line = 1;
    Line line(current_line);

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        line.add_token(&tokens[i]);

        if (tokens[i].get_token_type() == TokenType::SemiColon)
        {
            lines.push_back(std::move(line));
            ++current_line;
            line = Line(current_line);
        }
    }

    if (!line.empty())
        lines.push_back(std::move(line));

    return lines;
}

std::unique_ptr<ASTNode> Parser::parseFactor()
{
    const Token* current_token = current();

    if (line_ended() && current_token->get_token_type() != TokenType::SemiColon)
    {
        std::string msg = Errors::e_403();
        lines[line_pos].print_error(msg);
        ++parser_errors;
        return nullptr;
    }

    next_token();

    if (current_token->get_token_type() == TokenType::Numeric)
    {
        return std::make_unique<NumberExpr>(current_token->get_token_value());
    }
    else if (current_token->get_token_type() == TokenType::Alphanumeric)
    {
        return std::make_unique<VariableExpr>(current_token->get_token_value());
    }
    else if (current_token->get_token_type() == TokenType::OpenParen)
    {
        std::unique_ptr<ASTNode> expr = parseLowExpression();

        current_token = current();

        if (current_token->get_token_type() == TokenType::CloseParen)
        {
            return expr;
        }
        else
        {
            std::string msg = Errors::e_400(TokenType::CloseParen, current_token->get_token_type());
            lines[line_pos].print_error(current_token, msg);
            ++parser_errors;
            return nullptr;
        }
    }

    std::string msg = Errors::e_400(
        std::vector<TokenType>{TokenType::Numeric, TokenType::Alphanumeric, TokenType::OpenParen}, 
        current_token->get_token_type());
    lines[line_pos].print_error(current_token, msg);
    ++parser_errors;
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::parseMediumExpression()
{
    std::unique_ptr<ASTNode> left = parseFactor();
    if (left == nullptr) return nullptr;

    const Token* current_token = current();

    while (true)
    {
        TokenType op = current_token->get_token_type();

        if (op == TokenType::Multiply || op == TokenType::Divide || op == TokenType::Modulus)
        {
            next_token();          
            std::unique_ptr<ASTNode> right = parseFactor();
            if (right == nullptr) return nullptr;

            left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));

            current_token = current();
        }
        else if (Lexer::token_type_to_kind(op) != TokenKind::Arithmetic && op != TokenType::SemiColon)
        {
            std::string msg = Errors::e_400(TokenKind::Arithmetic, op);
            lines[line_pos].print_error(current_token, msg);
            ++parser_errors;
            return nullptr;
        }
        else
        {
            break;
        }
    }

    return left;
}
std::unique_ptr<ASTNode> Parser::parseLowExpression()
{
    std::unique_ptr<ASTNode> left = parseMediumExpression();
    if (left == nullptr) return nullptr;

    const Token* current_token = current();

    while (true)
    {
        TokenType op = current_token->get_token_type();

        if (op == TokenType::Plus || op == TokenType::Minus)
        {
            next_token();            
            std::unique_ptr<ASTNode> right = parseMediumExpression();
            if (right == nullptr) return nullptr;

            left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));

            current_token = current();
        }
        else if (Lexer::token_type_to_kind(op) != TokenKind::Arithmetic && op != TokenType::SemiColon)
        {
            std::string msg = Errors::e_400(TokenKind::Arithmetic, op);
            lines[line_pos].print_error(current_token, msg);
            ++parser_errors;
            return nullptr;
        }
        else
        {
            break;
        }
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parseVarDecl() 
{
    next_token();
    const Token* current_token = current();

    TokenType type;
    std::string name;

    if (current_token->get_token_type() == TokenType::Colon)
    {
        next_token();
        current_token = current();

        if (Lexer::token_type_to_kind(current_token->get_token_type()) == TokenKind::VariableType)
        {
            if (current_token->get_token_type() == TokenType::Void)
            {
                std::string msg = Errors::e_402();
                lines[line_pos].print_error(current_token, msg);
                ++parser_errors;
                return nullptr;
            }

            type = current_token->get_token_type();
        }
        else
        {
            std::string msg = Errors::e_400(TokenKind::VariableType, current_token->get_token_type());
            lines[line_pos].print_error(current_token, msg);
            ++parser_errors;
            return nullptr;
        }

        next_token();
        current_token = current();
    }
    else
    {
        type = TokenType::Any;
    }

    if (current_token->get_token_type() == TokenType::Alphanumeric)
    {
        name = current_token->get_token_value();
    }
    else
    {
        std::string msg = Errors::e_400(TokenType::Alphanumeric, current_token->get_token_type());
        lines[line_pos].print_error(current_token, msg);
        ++parser_errors;
        return nullptr;
    }

    next_token();
    current_token = current();

    std::unique_ptr<ASTNode> initExpr = nullptr;

    if (current_token->get_token_type() == TokenType::Assign) 
    {
        next_token();
        initExpr = parseLowExpression();
        if (initExpr == nullptr) return nullptr;

        current_token = current();
    }

    if (current_token->get_token_type() == TokenType::SemiColon)
    {
        return std::make_unique<VarDecl>(
            type,
            name,
            std::move(initExpr)
        );
    }
    else
    {
        std::string msg = Errors::e_400(
            std::vector<TokenType>{TokenType::SemiColon, TokenType::Assign},
            current_token->get_token_type());
        lines[line_pos].print_error(current_token, msg);
        ++parser_errors;
        return nullptr;
    }
}

std::unique_ptr<ASTNode> Parser::parseAssignmentStmt() 
{
    const Token* current_token = current();
    
    std::string name;
    TokenType assignOp;

    if (current_token->get_token_type() == TokenType::Alphanumeric)
    {
        name = current_token->get_token_value();
    }
    else
    {
        std::string msg = Errors::e_400(TokenType::Alphanumeric, current_token->get_token_type());
        lines[line_pos].print_error(current_token, msg);
        ++parser_errors;
        return nullptr;
    }

    next_token();
    current_token = current();

    if (Lexer::token_type_to_kind(current_token->get_token_type()) == TokenKind::Assignment)
    {
        assignOp = current_token->get_token_type();
    }
    else
    {
        std::string msg = Errors::e_400(TokenKind::Assignment, current_token->get_token_type());
        lines[line_pos].print_error(current_token, msg);
        ++parser_errors;
        return nullptr;
    }

    next_token();
    std::unique_ptr<ASTNode> assignExpr = parseLowExpression();
    current_token = current();

    if (assignExpr == nullptr)
    {
        return nullptr;
    }

    if (current_token->get_token_type() == TokenType::SemiColon)
    {
        return std::make_unique<AssignmentStmt>(
            assignOp,
            name,
            std::move(assignExpr)
        );
    }
    else
    {
        std::string msg = Errors::e_400(TokenType::SemiColon, current_token->get_token_type());
        lines[line_pos].print_error(current_token, msg);
        ++parser_errors;
        return nullptr;
    }
}

// --- Top-level parse ---
std::vector<std::unique_ptr<ASTNode>> Parser::parse() 
{
    std::vector<std::unique_ptr<ASTNode>> actions;

    if (lines.empty()) 
    {
        std::string msg = Errors::e_C00();
        std::cout << msg << std::endl;
        ++other_errors;

        print_status();
        return actions;
    }

    line_pos = 0;
    token_pos = 0;
    
    lexer_errors = 0;
    parser_errors = 0;
    other_errors = 0;

    for (const Line& line : lines)
    {
        for (const Token* token : line.get_tokens())
        {
            if (token->get_token_type() == TokenType::Syntax)
            {
                std::string msg = Errors::e_001(token->get_token_value());
                lines[line_pos].print_error(token, msg);
                ++lexer_errors;
                print_status();
                return std::vector<std::unique_ptr<ASTNode>>{};
            }
        }
    }

    for (const Line& line : lines)
    {
        if (line.empty())
        {
            next_line();
            continue;
        }

        const Token* current_token = current();

        if (current_token->get_token_type() == TokenType::VariableDeclaration)
        {
            actions.push_back(parseVarDecl());
        }
        else if (current_token->get_token_type() == TokenType::Alphanumeric)
        {
            actions.push_back(parseAssignmentStmt());
        }

        next_line();
    }

    for (const std::unique_ptr<ASTNode>& action : actions)
    {
        if (action == nullptr)
        {
            print_status();
            return std::vector<std::unique_ptr<ASTNode>>{};
        }
    }

    print_status();
    return actions;
}
