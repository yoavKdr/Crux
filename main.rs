mod lexer;
mod parser;
mod errors;

use lexer::lexer::Tokenizer;
use lexer::tokens::Token;
use parser::parser::Parser;


fn main() {
    let tokenizer: Tokenizer = Tokenizer::new();
    let tokens: Vec<Token> = tokenizer.tokeniztion(source());
    
    let lines = Parser::split_to_lines(tokens);

    for line in lines
    {
        line.is_valid();
    }
}

fn source() -> String
{
    "
    var hello = 3;
    var h = +;
    ".to_string()
}
