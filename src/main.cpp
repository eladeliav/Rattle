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

        if(input == "quit()" || input == "exit()")
            break;

        if(input == "clear()")
            std::cout << "\x1B[2J\x1B[H";

        Lexer lexer(input);
        Parser parser(lexer);
        Interpreter interpreter(parser);
        std::cout << interpreter.interpret() << std::endl;
    }
}