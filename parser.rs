#![allow(dead_code, unused_variables)]

pub mod expectations
{
    use crate::lexer::tokens::{Token, TokenKind, TokenType};

    pub enum TokenResult
    {
        Kind(TokenKind),
        KindVec(Vec<TokenKind>),
        KindVecType { token_kinds: Vec<TokenKind>, token_type: TokenType },

        Type(TokenType),
        TypeVec(Vec<TokenType>),
        TypeVecKind { token_kind: TokenKind, token_types: Vec<TokenType> },

        Both { token_kind: TokenKind, token_type: TokenType },
        BothVec { token_kinds: Vec<TokenKind>, token_types: Vec<TokenType> },
        None,
    }
    impl TokenResult
    {
        pub fn result_containing_token_type(result: &TokenResult, tt: &TokenType) -> bool
        {
            match result
            {
                TokenResult::Kind(token_kind) => 
                {
                    token_kind == &TokenKind::get_token_kind(tt)
                }
                TokenResult::KindVec(token_kinds) =>
                {
                    for token_kind in token_kinds
                    {
                        if token_kind == &TokenKind::get_token_kind(tt)
                        {
                            return true;
                        }
                    }

                    return false;
                }
                TokenResult::KindVecType{token_kinds, token_type} =>
                {
                    for token_kind in token_kinds
                    {
                        if token_kind == &TokenKind::get_token_kind(tt)
                        {
                            return true;
                        }
                    }
                    if token_type == tt
                    {
                        return true;
                    }
                    
                    return false;
                }

                TokenResult::Type(token_type) => 
                {
                    token_type == tt
                }
                TokenResult::TypeVec(token_types) =>
                {
                    for token_type in token_types
                    {
                        if token_type == tt
                        {
                            return true;
                        }
                    }

                    return false;
                }
                TokenResult::TypeVecKind{token_kind, token_types} =>
                {
                    for token_type in token_types
                    {
                        if token_type == tt
                        {
                            return true;
                        }
                    }
                    if token_kind == &TokenKind::get_token_kind(tt)
                    {
                        return true;
                    }

                    return false;
                }

                TokenResult::Both { token_kind, token_type } =>
                {
                    if token_kind == &TokenKind::get_token_kind(tt) || token_type == tt
                    {
                        return true;
                    }

                    return false;
                }
                TokenResult::BothVec { token_kinds, token_types } =>
                {
                    for token_kind in token_kinds
                    {
                        if token_kind == &TokenKind::get_token_kind(tt)
                        {
                            return true;
                        }
                    }
                    for token_type in token_types
                    {
                        if token_type == tt
                        {
                            return true;
                        }
                    }

                    return false;
                }

                TokenResult::None => false
            }
        }
    
        pub fn content(&self) -> String
        {
            match &self
            {
                TokenResult::Kind(token_kind) => 
                {
                    let msg = format!("\n\t  Token kind: {}", token_kind);
                    msg
                }
                TokenResult::KindVec(token_kinds) =>
                {
                    let mut msg = format!("\n\t  Token kind:");
                    for token_kind in token_kinds
                    {
                        msg = format!("{} {},", msg, token_kind);
                    }

                    msg
                }
                TokenResult::KindVecType{token_kinds, token_type} =>
                {
                    let mut msg = format!("\n\t  Token kind:");
                    for token_kind in token_kinds
                    {
                        msg = format!("{} {},", msg, token_kind);
                    }
                
                    msg = format!("{}\n\t  Token type: {}", msg, token_type);

                    msg
                }

                TokenResult::Type(token_type) => 
                {
                    let msg = format!("\n\t  Token type: {}", token_type);
                    msg
                }
                TokenResult::TypeVec(token_types) =>
                {
                    let mut msg = format!("\n\t  Token type:");
                    for token_type in token_types
                    {
                        msg = format!("{} {},", msg, token_type);
                    }

                    msg
                }
                TokenResult::TypeVecKind{token_kind, token_types} =>
                {
                    let mut msg = format!("\n\t  Token kind: {}", token_kind);

                    msg = format!("{}\n\t  Token type:", msg);
                    for token_type in token_types
                    {
                        msg = format!("{} {},", msg, token_type);
                    }

                    msg
                }

                TokenResult::Both { token_kind, token_type } =>
                {
                    let msg = format!("\n\t  Token kind: {} | Token type: {}", token_kind, token_type);
                    msg
                }
                TokenResult::BothVec { token_kinds, token_types } =>
                {
                    let mut msg = format!("\n\t  Token kind:");
                    for token_kind in token_kinds
                    {
                        msg = format!("{} {},", msg, token_kind);
                    }
                    msg = format!("{}\n\t  Token type:", msg);
                    for token_type in token_types
                    {
                        msg = format!("{} {},", msg, token_type);
                    }

                    msg
                }

                TokenResult::None => 
                {
                    let msg = format!("Empty");
                    msg
                }
            }
        }
    }

    pub struct Expectations;
    impl Expectations
    {
        // ------------ Sorting ------------
        pub fn sorting(token: &Token) -> TokenResult
        {
            match TokenKind::get_token_kind(token.get_token_type())
            {
                TokenKind::Assignment => Expectations::after_assignment(),
                TokenKind::Arithmetic => Expectations::after_arithmetic(),
                TokenKind::Declaration => Expectations::after_declaration(),
                TokenKind::Data => Expectations::after_data(token.get_token_type()),

                _ => Expectations::others(token.get_token_type()),
            }
        }

        // ------------ Assignment ------------
        fn after_assignment() -> TokenResult
        {
            TokenResult::Kind(TokenKind::Data)
        }

        // ------------ Arithmetic ------------
        fn after_arithmetic() -> TokenResult
        {
            TokenResult::Type(TokenType::Numeric)
        }

        // ------------ Declaration ------------
        fn after_declaration() -> TokenResult
        {
            TokenResult::Type(TokenType::Alphanumeric)
        }

        // ------------ Data ------------
        fn after_data(token_type: &TokenType) -> TokenResult
        {
            match token_type
            {
                TokenType::Alphanumeric => Expectations::after_alphanumeric(),
                TokenType::Numeric => Expectations::after_numeric(),
                TokenType::Text => Expectations::after_text(),

                _ => TokenResult::None
            }
        }
        
        fn after_alphanumeric() -> TokenResult
        {
            TokenResult::Both
            {
                token_kind: TokenKind::Assignment,
                token_type: TokenType::Eol,
            }
        }
        fn after_numeric() -> TokenResult
        {
            TokenResult::Both
            {
                token_kind: TokenKind::Arithmetic,
                token_type: TokenType::Eol,
            }        
        }
        fn after_text() -> TokenResult
        {
            TokenResult::Type(TokenType::Eol)       
        }

        // ------------ Other ------------
        fn others(token_type: &TokenType) -> TokenResult
        {
            match token_type
            {
                TokenType::Empty => Expectations::first_token(),
                TokenType::Eol => Expectations::after_end_of_line(),

                _ => TokenResult::None
            }
        }

        fn first_token() -> TokenResult
        {
            TokenResult::TypeVecKind
            {
                token_kind: TokenKind::Declaration,
                token_types: vec![TokenType::Variable, TokenType::Function, TokenType::Numeric],
            }
        }
        fn after_end_of_line() -> TokenResult
        {
            TokenResult::None  
        }

    }
}

pub mod parser
{
    use crate::{errors::errors::{LexerErrors, ParserErrors}, lexer::tokens::{Token, TokenKind, TokenType}};
    use super::expectations::{TokenResult, Expectations};
    use std::collections::VecDeque;
    use std::ptr;


    pub struct AST
    {
        value: Token,
        left: Option<Box<AST>>,
        right: Option<Box<AST>>,
    }
    // init
    impl AST
    {
        pub fn new(value: Token, left: Option<AST>, right: Option<AST>) -> Self 
        {
            Self 
            {
                value,
                left: left.map(Box::new),
                right: right.map(Box::new),
            }
        }
        pub fn empty() -> Self
        {
            Self
            {
                value: Token::empty(),
                left: None,
                right: None,
            }
        }
    }
    // getters + setters
    impl AST
    {
        pub fn get_token(&self) -> &Token
        {
            &self.value
        }
        pub fn get_left(&self) -> &Option<Box<AST>>
        {
            &self.left
        }
        pub fn get_right(&self) -> &Option<Box<AST>>
        {
            &self.right
        }

        pub fn set_token(&mut self, token: Token)
        {
            self.value = token;
        }
        pub fn set_left(&mut self, token: Option<Box<AST>>)
        {
            self.left = token;
        }
        pub fn set_right(&mut self, token: Option<Box<AST>>)
        {
            self.right = token;
        }    
    }
    // cmds
    impl AST
    {
        pub fn dead_end(&self) -> bool
        {
            self.left.is_none() && self.right.is_none()
        }
        pub fn next(&self) -> Option<&AST>
        {
            if let Some(left) = &self.left
            {
                if !left.dead_end() {
                    return Some(left);
                }
            }

            if let Some(right) = &self.right
            {
                if !right.dead_end() {
                    return Some(right);
                }
            }

            None
        }

        pub fn print_tree(&self, depth: usize)
        {
            if let Some(right) = &self.right
            {
                right.print_tree(depth + 1);
            }
            println!("{}{}", "  ".repeat(depth), self.value.get_token_value());
            if let Some(left) = &self.left
            {
                left.print_tree(depth + 1);
            }
        }
        /*pub fn calculate_mathematical_ast(start: &AST) -> Token
        {
            let mut stack: Vec<&AST> = Vec::new();
            let mut current_ast= start;

            while let Some(new_ast) = current_ast.next()
            {
                current_ast = new_ast;
                stack.push(new_ast);
            }

            if current_ast.dead_end()
            {
                return current_ast.get_token().clone();
            }
            else 
            {
                
            }

            Token::empty()
        }*/
    }


    pub struct Line
    {
        tokens: Vec<Token>,
    }
    // init
    impl Line
    {
        pub fn new() -> Self
        {
            Self 
            {
                tokens: Vec::new(),
            }
        }
    }
    // getter + setter
    impl Line
    {
        pub fn get_tokens(&self) -> &Vec<Token>
        {
            &self.tokens
        }
        pub fn add_token(&mut self, token: Token)
        {
            self.tokens.push(token);
        }
    }
    // cmds
    impl Line
    {
        pub fn is_valid(&self) -> bool
        {
            let mut last_token: &Token = &Token::empty();

            for token in &self.tokens
            {
                if *token.get_token_type() == TokenType::Syntax
                {
                    let msg = LexerErrors::unidentified_syntax(token.get_token_value());

                    self.print();
                    self.point_at_token(token);
                    println!("{}", msg);

                    return false;
                }

                let token_result = &Expectations::sorting(last_token);
                if !(&TokenResult::result_containing_token_type(token_result,token.get_token_type()))
                {
                    let msg = ParserErrors::expectation_error(token_result, token.get_token_type());
                        
                    self.print();
                    self.point_at_token(token);
                    println!("{}", msg);
                    return false;
                }

                last_token = &token;
            }

            true
        }
        
        pub fn print(&self)
        {
            for token in &self.tokens
            {
                print!("{} ", token.get_token_value());
            }
            print!("\n");
        }
        pub fn print_as_tokens(&self)
        {
            for token in &self.tokens
            {
                token.print();
            }
        }    
        pub fn point_at_token(&self, token: &Token)
        {
            for t in &self.tokens
            {
                if ptr::eq(t, token)
                {
                    for _ in t.get_token_value().chars()
                    {
                        print!("^");
                    }
                }
                else
                {
                    for _ in t.get_token_value().chars()
                    {
                        print!("-");
                    }
                    print!("-");
                }
            }
            print!("\n");
        }
    }

    pub struct Parser;
    impl Parser
    {
        pub fn split_to_lines(tokens: Vec<Token>) -> Vec<Line>
        {
            let mut lines: Vec<Line> = Vec::new();
    
            let mut line = Line::new();
            for token in tokens
            {
                if *token.get_token_type() as i32 == TokenType::Eol as i32 {
                    line.add_token(token);
                    lines.push(line);
                    line = Line::new();
                }
                else 
                {
                    line.add_token(token);
                }
            }
    
            lines
        }

        // need fix
        pub fn mathematical_parsing(tokens: &[Token]) -> Option<AST>
        {
            let mut output: VecDeque<AST> = VecDeque::new();
            let mut operators: Vec<Token> = Vec::new();
        
            for token in tokens
            {
                match token.get_token_type()
                {
                    TokenType::Numeric =>
                    {
                        output.push_back(AST::empty());
                    }
                    TokenType::Plus | TokenType::Minus | TokenType::Multiply | TokenType::Divide | TokenType::Modulus =>
                    {
                        while let Some(op) = operators.last() {
                            if TokenKind::get_arithmetic_precedence(&op.get_token_type()) >= TokenKind::get_arithmetic_precedence(&token.get_token_type())
                            {
                                let right = output.pop_back();
                                let left = output.pop_back();
                                if let (Some(l), Some(r)) = (left, right)
                                {
                                    output.push_back(AST::new(operators.pop().unwrap(), Some(l), Some(r)));
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        operators.push(token.clone());
                    }

                    _=> return None,
                }
            }
            
            while let Some(op) = operators.pop()
            {
                let right = output.pop_back();
                let left = output.pop_back();
                if let (Some(l), Some(r)) = (left, right) {
                    output.push_back(AST::new(op, Some(l), Some(r)));
                }
            }
            
            output.pop_front()
        }
    }
}