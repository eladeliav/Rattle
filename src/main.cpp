#include <iostream>
#include "lexer/Lexer.hpp"
using namespace Lexer;
int main()
{
    while(true)
    {
        std::string input;
        std::getline(std::cin, input);

        if(input == "quit")
            break;

        Lexer::Lex lex(input);
        std::string result = lex.runExpression();
        std::cout << result << std::endl;
    }
}