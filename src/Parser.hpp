//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_PARSER_HPP
#define RATTLE_PARSER_HPP
#include "Lexer.hpp"
#include "BinOp.hpp"

class Parser
{
private:
    Lexer lex;
    Token currentToken;
public:
    explicit Parser(Lexer lex);
    BinOp* parse();
private:
    void eat(Token::Type type);
    BinOp* factor();
    BinOp* term();
    BinOp* expr();
};


#endif //RATTLE_PARSER_HPP
