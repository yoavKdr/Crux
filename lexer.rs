#![allow(dead_code, unused_variables)]

pub mod tokens
{
    use std::fmt;

    #[derive(PartialEq)]
    pub enum TokenKind
    {
        Error = 0,
        File,
        Assignment,
        Arithmetic,
        Relational,
        Gates,
        VariableType,
        Declaration,
        Variable,
        Function,
        Data,
        Other,
        Whitespace,
    }
    impl TokenKind
    {
        pub fn get_token_kind(token_type: &TokenType) -> TokenKind
        {
            match *token_type as i32
            {
                v if v >= TokenType::ESP as i32 && v <= TokenType::EEP as i32 => TokenKind::Error,
                v if v >= TokenType::FSP as i32 && v <= TokenType::FEP as i32 => TokenKind::File,
                v if v >= TokenType::ASSP as i32 && v <= TokenType::ASEP as i32 => TokenKind::Assignment,
                v if v >= TokenType::ARSP as i32 && v <= TokenType::AREP as i32 => TokenKind::Arithmetic,
                v if v >= TokenType::RSP as i32 && v <= TokenType::REP as i32 => TokenKind::Relational,
                v if v >= TokenType::GSP as i32 && v <= TokenType::GEP as i32 => TokenKind::Gates,
                v if v >= TokenType::VTSP as i32 && v <= TokenType::VTEP as i32 => TokenKind::VariableType,
                v if v >= TokenType::DESP as i32 && v <= TokenType::DEEP as i32 => TokenKind::Declaration,
                v if v == TokenType::Variable as i32 => TokenKind::Variable,
                v if v == TokenType::Function as i32 => TokenKind::Function,
                v if v >= TokenType::DASP as i32 && v <= TokenType::DAEP as i32 => TokenKind::Data,
                v if v >= TokenType::OSP as i32 && v <= TokenType::OEP as i32 => TokenKind::Data,
                v if v >= TokenType::WSSP as i32 && v <= TokenType::WSEP as i32 => TokenKind::Data,

                _ => TokenKind::Error,
            }
        }

        // ------------ Arithmetic ------------
        pub fn get_arithmetic_precedence(token_type: &TokenType) -> u8
        {
            match token_type
            {
                TokenType::Plus | TokenType::Minus => 1,
                TokenType::Multiply | TokenType::Divide | TokenType::Modulus => 2,
                _ => 0,
            }
        }

        pub fn get_numeric_type(value: String) -> TokenType
        {
            if let Ok(n) = value.parse::<i128>()
            {
                if n >= i8::MIN as i128 && n <= i8::MAX as i128
                {
                    return TokenType::Int8;
                }
                else if n >= i16::MIN as i128 && n <= i16::MAX as i128
                {
                    return TokenType::Int16;
                }
                else if n >= i32::MIN as i128 && n <= i32::MAX as i128
                {
                    return TokenType::Int32;
                }
                else if n >= i64::MIN as i128 && n <= i64::MAX as i128
                {
                    return TokenType::Int64;
                }
                else
                {
                    return TokenType::Int128;
                }
            }
            else if let Ok(n) = value.parse::<f64>()
            {
                if n >= f32::MIN as f64 && n <= f32::MAX as f64
                {
                    return TokenType::Float32;
                }
                else
                {
                    return TokenType::Float64;
                }
            }
            else
            {
                TokenType::Unknown
            }
        }
    
        // ------------ Declerations ------------
        pub fn is_declerations_token_type(token_type: &TokenType) -> bool
        {
            match token_type
            {
                TokenType::NewFunction => true,
                TokenType::NewVariable => true,
                _=> false,
            }
        }

    }
    impl fmt::Display for TokenKind
    {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            match self {
                TokenKind::Error         => write!(f, "Error"),
                TokenKind::File          => write!(f, "File"),
                TokenKind::Assignment    => write!(f, "Assignment"),
                TokenKind::Arithmetic    => write!(f, "Arithmetic"),
                TokenKind::Relational    => write!(f, "Relational"),
                TokenKind::Gates         => write!(f, "Gates"),
                TokenKind::VariableType => write!(f, "VariableType"),
                TokenKind::Declaration  => write!(f, "Declaration"),
                TokenKind::Variable      => write!(f, "Variable"),
                TokenKind::Function      => write!(f, "Function"),
                TokenKind::Data          => write!(f, "Data"),
                TokenKind::Other         => write!(f, "Other"),
                TokenKind::Whitespace    => write!(f, "Whitespace"),
            }
        }
    }

    #[derive(Debug, Hash, Eq, PartialEq, Copy, Clone)]
    pub enum TokenType
    {
        // ------------ Error ------------
        ESP,
        Empty, // there is no value
        Unknown, // for unknown values
        Syntax, // write error
        EEP,

        // ------------ File ------------
        FSP,
        Sof, // Start Of File
        Eof, // End Of File
        Sol, // Start Of Line
        Eol, // End Of Line
        FEP,


        // ------------ Assignment Operators ------------
        ASSP,
        Assign, // =
        PlusAssign, // +=
        MinusAssign, // -=
        MultiplyAssign, // *=
        DivideAssign, // /=
        ModulusAssign, // %=
        ASEP,

        // ------------ Arithmetic Operators ------------
        ARSP,
        Plus, // +
        Minus, // -
        Multiply, // *
        Divide, // /
        Modulus, // %
        AREP,

        // ------------ Relational Operators ------------
        RSP,
        Less, // <
        Greater, // >
        LessEqual, // <=
        GreaterEqual, // >=
        Equal, // ==
        NotEqual, // !=
        REP,

        // ------------ Gates Operators ------------
        GSP,
        And, // &&
        Or, // ||
        Not, // !
        GEP,

        // ------------ Variable Types ------------
        VTSP,
        // --- int ---
        Int8,
        Int16,
        Int32,
        Int64,
        Int128,
        // --- unsigned int ---
        UnsignedInt8,
        UnsignedInt16,
        UnsignedInt32,
        UnsignedInt64,
        UnsignedInt128,
        // --- float ---
        Float32,
        Float64,
        // --- char ---
        Char,
        String,
        // --- Others ---
        Bool,
        VTEP,

        // ------------ Declerations ------------
        DESP,
        NewVariable,
        NewFunction,
        DEEP,

        // ------------ Variable ------------
        Variable, // Variable

        // ------------ Functions ------------
        Function, // Function

        // ------------ Data ------------
        DASP,
        Alphanumeric, // can be a var
        Numeric, // numbers
        Text, // texts
        DAEP,

        // ------------ Other ------------
        OSP,
        Dot, // .
        Comma, // ,
        Colon, // :
        Semicolon, // ;
        OpenParen, // (
        CloseParen, // )
        OpenBrace, // {
        CloseBrace, // }
        OpenBracket, // [
        CloseBracket, // ]
        OEP,

        // ------------ Whitespace ------------
        WSSP,
        Space, // ' '
        HorizontalTab, // \t
        Newline, // \n
        CarriageReturn, // \r
        FormFeed, // \f
        VerticalTab, // \v
        WSEP,
    }
    impl fmt::Display for TokenType
    {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result 
        {
            match self 
            {
                // ------------ Error ------------
                TokenType::Empty => write!(f, "Empty"),
                TokenType::Unknown => write!(f, "Unknown"),
                TokenType::Syntax => write!(f, "Syntax"),

                // ------------ File ------------
                TokenType::Sof => write!(f, "Sof"),
                TokenType::Eof => write!(f, "Eof"),
                TokenType::Sol => write!(f, "Sol"),
                TokenType::Eol => write!(f, "Eol"),

                // ------------ Assignment Operators ------------
                TokenType::Assign => write!(f, "Assign"),
                TokenType::PlusAssign => write!(f, "PlusAssign"),
                TokenType::MinusAssign => write!(f, "MinusAssign"),
                TokenType::MultiplyAssign => write!(f, "MultiplyAssign"),
                TokenType::DivideAssign => write!(f, "DivideAssign"),
                TokenType::ModulusAssign => write!(f, "ModulusAssign"),

                // ------------ Arithmetic Operators ------------
                TokenType::Plus => write!(f, "Plus"),
                TokenType::Minus => write!(f, "Minus"),
                TokenType::Multiply => write!(f, "Multiply"),
                TokenType::Divide => write!(f, "Divide"),
                TokenType::Modulus => write!(f, "Modulus"),

                // ------------ Relational Operators ------------
                TokenType::Less => write!(f, "Less"),
                TokenType::Greater => write!(f, "Greater"),
                TokenType::LessEqual => write!(f, "LessEqual"),
                TokenType::GreaterEqual => write!(f, "GreaterEqual"),
                TokenType::Equal => write!(f, "Equal"),
                TokenType::NotEqual => write!(f, "NotEqual"),

                // ------------ Gates Operators ------------
                TokenType::And => write!(f, "And"),
                TokenType::Or => write!(f, "Or"),
                TokenType::Not => write!(f, "Not"),

                // ------------ Variable Types ------------
                TokenType::Int8 => write!(f, "Int8"),
                TokenType::Int16 => write!(f, "Int16"),
                TokenType::Int32 => write!(f, "Int32"),
                TokenType::Int64 => write!(f, "Int64"),
                TokenType::Int128 => write!(f, "Int128"),

                TokenType::UnsignedInt8 => write!(f, "Int8"),
                TokenType::UnsignedInt16 => write!(f, "Int16"),
                TokenType::UnsignedInt32 => write!(f, "Int32"),
                TokenType::UnsignedInt64 => write!(f, "Int64"),
                TokenType::UnsignedInt128 => write!(f, "Int128"),

                TokenType::Float32 => write!(f, "Float32"),
                TokenType::Float64 => write!(f, "Float64"),

                TokenType::Char => write!(f, "Char"),
                TokenType::String => write!(f, "String"),

                TokenType::Bool => write!(f, "Bool"),

                // ------------ Declerations ------------
                TokenType::NewVariable => write!(f, "NewVariable"),
                TokenType::NewFunction => write!(f, "NewFunction"),

                // ------------ Variable ------------
                TokenType::Variable => write!(f, "Variable"),

                // ------------ Functions ------------
                TokenType::Function => write!(f, "Function"),

                // ------------ Data ------------
                TokenType::Alphanumeric => write!(f, "Alphanumeric"),
                TokenType::Numeric => write!(f, "Numeric"),
                TokenType::Text => write!(f, "Text"),

                // ------------ Other ------------
                TokenType::Dot => write!(f, "Dot"),
                TokenType::Comma => write!(f, "Comma"),
                TokenType::Colon => write!(f, "Colon"),
                TokenType::Semicolon => write!(f, "Semicolon"),
                TokenType::OpenParen => write!(f, "OpenParen"),
                TokenType::CloseParen => write!(f, "CloseParen"),
                TokenType::OpenBrace => write!(f, "OpenBrace"),
                TokenType::CloseBrace => write!(f, "CloseBrace"),
                TokenType::OpenBracket => write!(f, "OpenBracket"),
                TokenType::CloseBracket => write!(f, "CloseBracket"),


                // ------------ Whitespace ------------
                TokenType::Space => write!(f, "Space"),
                TokenType::HorizontalTab => write!(f, "HorizontalTab"),
                TokenType::Newline => write!(f, "Newline"),
                TokenType::CarriageReturn => write!(f, "CarriageReturn"),
                TokenType::FormFeed => write!(f, "FormFeed"),
                TokenType::VerticalTab => write!(f, "VerticalTab"),

                _ => write!(f, "Unknown"),
            }
        }
    }

    #[derive(Clone)]
    pub struct Token
    {
        token_type: TokenType,
        token_value: String,
    }
    // init
    impl Token
    {
        pub fn new(token_value: String, token_type: TokenType) -> Self 
        {
            Self{ token_type, token_value }
        }

        pub fn empty() -> Self
        {
            Self
            {
                token_type: TokenType::Empty,
                token_value: String::new(),
            }
        }
    }
    // getters + setters
    impl Token 
    {
        pub fn get_token_type(&self) -> &TokenType
        {
            return &self.token_type;
        }
        pub fn get_token_value(&self) -> &String
        {
            return &self.token_value;
        }

        pub fn set_token_type(&mut self, token_type: TokenType)
        {
            self.token_type = token_type;
        }
        pub fn set_token_value(&mut self, value: String)
        {
            self.token_value = value;
        }
    }
    // cmd
    impl Token
    {
        pub fn print(&self)
        {
            println!("Token: {0} | Type: {1}", &self.token_value, &self.token_type)
        }
    }
}

pub mod lexer
{
    use super::tokens::{Token, TokenType};
    use std::collections::HashMap;
    
    pub struct Tokenizer
    {
        token_type_map: HashMap<TokenType, &'static str>,
    }
    // init
    impl Tokenizer
    {
        pub fn new() -> Self 
        {
            Self 
            {
                token_type_map: Tokenizer::token_map(),
            }
        }
        fn token_map() -> HashMap<TokenType, &'static str>
        {
            let mut map: HashMap<TokenType, &'static str> = HashMap::new();
    
            // ------------ Assignment ------------
            map.insert(TokenType::Assign, "=");
            map.insert(TokenType::PlusAssign, "+=");
            map.insert(TokenType::MinusAssign, "-=");
            map.insert(TokenType::MultiplyAssign, "*=");
            map.insert(TokenType::DivideAssign, "/=");
            map.insert(TokenType::ModulusAssign, "%=");

            // ------------ Arithmetic ------------
            map.insert(TokenType::Plus, "+");
            map.insert(TokenType::Minus, "-");
            map.insert(TokenType::Multiply, "*");
            map.insert(TokenType::Divide, "/");
            map.insert(TokenType::Modulus, "%");
    
            // ------------ Relational ------------
            map.insert(TokenType::Less, "<");
            map.insert(TokenType::Greater, ">");
            map.insert(TokenType::LessEqual, "<=");
            map.insert(TokenType::GreaterEqual, ">=");
            map.insert(TokenType::Equal, "==");
            map.insert(TokenType::NotEqual, "!=");
    
            // ------------ Gates ------------
            map.insert(TokenType::And, "&&");
            map.insert(TokenType::Or, "||");
            map.insert(TokenType::Not, "!");

            // ------------ VariableTypes ------------
            map.insert(TokenType::Int8, "i8");
            map.insert(TokenType::Int16, "i16");
            map.insert(TokenType::Int32, "i32");
            map.insert(TokenType::Int64, "i64");
            map.insert(TokenType::Int128, "i128");

            map.insert(TokenType::UnsignedInt8, "u8");
            map.insert(TokenType::UnsignedInt16, "u16");
            map.insert(TokenType::UnsignedInt32, "u32");
            map.insert(TokenType::UnsignedInt64, "u64");
            map.insert(TokenType::UnsignedInt128, "u128");

            map.insert(TokenType::Float32, "f32");
            map.insert(TokenType::Float64, "f64");

            map.insert(TokenType::Char, "char");
            map.insert(TokenType::String, "string");

            map.insert(TokenType::Bool, "bool");

            // ------------ Declerations ------------
            map.insert(TokenType::NewFunction, "func");
            map.insert(TokenType::NewVariable, "var");            

            // ------------ Other ------------
            map.insert(TokenType::Dot, ".");
            map.insert(TokenType::Comma, ",");
            map.insert(TokenType::Colon, ":");
            map.insert(TokenType::Eol, ";");
            map.insert(TokenType::OpenParen, "(");
            map.insert(TokenType::CloseParen, ")");
            map.insert(TokenType::OpenBrace, "{");
            map.insert(TokenType::CloseBrace, "}");
            map.insert(TokenType::OpenBracket, "[");
            map.insert(TokenType::CloseBracket, "]");
    
            map
        }
    }
    // token type control
    impl Tokenizer
    {
        pub fn add_token_type(&mut self, token_type: TokenType, value: &'static str)
        {
            self.token_type_map.insert(token_type, value);
        }

        pub fn string_to_token_type(&self, value: &str) -> TokenType
        {
            let tt: TokenType = self.token_type_map
                .iter()
                .find_map(|(key, &val)| if val == value { Some(*key) } else { None })
                .unwrap_or(TokenType::Unknown);

            if tt != TokenType::Unknown
            {
                return tt;
            }
            if Tokenizer::has_quotes(value)
            {
                return TokenType::Text;
            }
            if Tokenizer::is_numeric(value)
            {
                return TokenType::Numeric;
            }
            if Tokenizer::is_alphanumeric_or_underscore(value)
            {
                return TokenType::Alphanumeric;
            }

            return tt;
        }
        pub fn token_type_to_string(&self, token_type: TokenType) -> &'static str
        {
            self.token_type_map
                .get(&token_type)
                .copied()
                .unwrap_or("")
        }  
        pub fn string_is_token_type(&self, value: &str) -> bool
        {
            self.string_to_token_type(value) != TokenType::Unknown
        }
    
        fn is_numeric(s: &str) -> bool 
        {
            s.parse::<i64>().is_ok() || s.parse::<f64>().is_ok()
        }

        fn is_alphanumeric(s: &str) -> bool 
        {
            s.chars().all(|c| c.is_alphanumeric())
        }
        fn is_alphanumeric_or_underscore(s: &str) -> bool 
        {
            s.chars().all(|c| c.is_alphanumeric() || c == '_')
        }

        fn has_quotes(s: &str) -> bool 
        {
            if s.len() <= 1
            {
                return false; 
            }
            s.starts_with('"') && s.ends_with('"')
        }
    }

    impl Tokenizer
    {
        fn split_from_operators<'a>(&self, source: &'a str) -> Vec<&'a str>
        {
            let mut results: Vec<&'a str> = Vec::new();
            
            let mut start_index: usize = 0;

            for (location, next_char) in source.chars().enumerate()
            {
                let new_word: &'a str = &source[start_index..=location];
                if self.string_to_token_type(&new_word) != TokenType::Unknown
                {
                    if location + 1 >= source.len()
                    {
                        results.push(new_word);
                    }
                    else if !self.string_is_token_type(
                        &(new_word.to_string() + 
                        &source.chars().nth(location + 1).unwrap_or_default().to_string()))
                    {
                        results.push(new_word);
                        start_index = location + 1;
                    }
                }
                else if location + 1 >= source.len()
                {
                    results.push(new_word);
                }
            }
    
            return results;
        }

        pub fn tokeniztion(&self, source: String) -> Vec<Token>
        {
            let mut tokens:Vec<Token>  = Vec::new();

            for word in source.split_whitespace()
            {
                let token_type: TokenType = self.string_to_token_type(word);

                let mut tt = self.string_to_token_type(word);
                if tt != TokenType::Unknown
                {
                    tokens.push(Token::new(word.to_string(), tt));

                    continue;
                }

                for new_word in self.split_from_operators(word)
                {
                    tt = self.string_to_token_type(new_word);

                    if tt == TokenType::Unknown
                    {
                        tt = TokenType::Syntax;
                    }

                    tokens.push(Token::new(new_word.to_string(), tt));
                }
            }

            tokens
        }
    
        pub fn print_tokens(tokens: &Vec<Token>)
        {
            for token in tokens
            {
                token.print();
            }
        }
    }

}