#include "lexer/Lexer.hpp"
#include <iostream>
#include <map>
using namespace Lexer;
int main()
{
    std::map<Token::Type, std::string> m{
            {Token::Type::KEYWORD, "Keyword"},
            {Token::Type::WHITESPACE, "Whitespace"},
            {Token::Type::LITERAL, "Literal"},
            {Token::Type::OPERATOR, "Operator"},
            {Token::Type::IDENTIFIER, "Identifier"},
            {Token::Type::DELIMINATOR, "Deliminator"}
    };
    auto vec = Lexer::tokenize("code.txt");

    for(Token x : vec)
    {
        std::cout << x.getValue() << "->" << m.find(x.getTokenType())->second << std::endl;
    }
}