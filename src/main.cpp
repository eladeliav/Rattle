#include <iostream>
#include "lexer/Lex.hpp"
#include "lexer/Parser.hpp"

using namespace Lexer;
int main()
{
    while(true)
    {
        std::string input;
        std::getline(std::cin, input);

        if(input == "quit")
            break;

        Lex lex(input);
        Parser parser(lex);
        std::cout << parser.expr() << std::endl;
    }
}