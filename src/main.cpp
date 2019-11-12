#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

int main()
{
    while(true)
    {
        std::string input;
        std::getline(std::cin, input);

        if(input == "quit")
            break;

        Lexer lexer(input);
        Parser parser(lexer);
        Interpreter interpreter(parser);
        std::cout << interpreter.interpret() << std::endl;
    }
}