//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_PARSER_HPP
#define RATTLE_PARSER_HPP
#include "Lex.hpp"

using namespace Lexer;

class Parser
{
private:
    Lex lex;
    Token currentToken;
public:
    explicit Parser(Lex lex);
    std::string expr();
private:
    void eat(Token::Type type);
    int factor();
    int term();
};


#endif //RATTLE_PARSER_HPP
