#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

#include "lexer.h"
#include "parser/parser.h"
#include "compiler/compiler.h"


// Helper: read entire file into a string
static std::string read_file_to_string(const std::string& path)
{
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in)
    {
        throw std::runtime_error("Error: could not open file '" + path + "'");
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

// Helper: check if filename ends with ".cx"
static bool has_cx_extension(const std::string& filename)
{
    const std::string ext = ".cx";
    if (filename.size() < ext.size()) return false;
    return filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <source_file.cx>\n";
        return 1;
    }
    std::string in_path = argv[1];
    if (!has_cx_extension(in_path))
    {
        std::cerr << "Error: input file must have .cx extension\n";
        return 1;
    }
    std::string source;
    try
    {
        source = read_file_to_string(in_path);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }


    Lexer lexer;

    std::vector<Token> tokens = lexer.tokenization(source);

    Parser parser(tokens);

    std::vector<std::unique_ptr<ASTNode>> asts = parser.parse();
    for(const std::unique_ptr<ASTNode>& ast : asts)
    {
        if (ast != nullptr)
        {
            ast->print();
        }
    }

    Compiler compiler;

    compiler.compile(asts);
    compiler.printSymbols();

    return 0;
}