#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include <fstream>

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        // got file, try to open
        std::ifstream ifs(argv[1]);
        ifs >> std::noskipws;
        std::string line;
        std::string prog;
        while(std::getline(ifs, line))
        {
            prog+=line + "\n";

        }
        Lexer lexer(prog);
        Parser parser(lexer);
        Interpreter interpreter(parser);
        interpreter.interpret();
        exit(0);
    }
    while(true)
    {
        std::string input;
        std::getline(std::cin, input);

        if(input == "quit()" || input == "exit()")
            exit(0);

        Lexer lexer(input);
        Parser parser(lexer);
        Interpreter interpreter(parser);
        std::cout << interpreter.interpret() << std::endl;
    }
}