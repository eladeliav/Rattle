//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_PARSER_HPP
#define RATTLE_PARSER_HPP
#include "Lexer.hpp"
#include "IfNode.hpp"
#include "BinNode.hpp"
#include "BlockNode.hpp"
#include "FunctionNode.hpp"
#include <vector>

class Parser
{
private:
    Lexer lex;
    Token currentToken;
    IfNode* lastIf;
public:
    explicit Parser(Lexer lex);
    BinNode* parse();
private:
    void eat(Token::Type type);
    BinNode* factor();
    BinNode* term();
    BinNode* expr();
    BlockNode* getBlock();
};


#endif //RATTLE_PARSER_HPP
