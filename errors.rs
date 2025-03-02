#![allow(dead_code, unused_variables)]

pub mod errors
{
    use crate::{lexer::tokens::TokenType, parser::expectations::TokenResult};
    pub struct ParserErrors;
    impl ParserErrors
    {
        pub fn expectation_error(expected: &TokenResult ,found: &TokenType) -> String
        {
            let mut msg  = format!("Parser Error: unexpected token has been found");
            msg = format!("{}\n\tExpected: {}", msg, expected.content());
            msg = format!("{}\n\tfound: {}", msg, found);
            msg
        }
    }

    pub struct LexerErrors;
    impl LexerErrors
    {
        pub fn unidentified_syntax(s: &str) -> String
        {
            let msg  = format!("Lexer Error: unidentified string \"{}\"", s);
            msg
        }
    }
}