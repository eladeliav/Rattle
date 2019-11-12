//
// Created by elade on 11/12/2019.
//

#include "Parser.hpp"
void Parser::eat(Token::Type type)
{
    if(currentToken.getType() == type)
        currentToken = lex.getNextToken();
    else
        throw(std::runtime_error("Unexpected Token"));
}

std::string Parser::expr()
{
    int res = term();

    while(currentToken.getType() == Token::Type::PLUS || currentToken.getType() == Token::Type::MINUS)
    {
        Token token = currentToken;
        if(token.getType() == Token::Type::PLUS)
        {
            eat(Token::Type::PLUS);
            res += term();
        }
        else if(token.getType() == Token::Type::MINUS)
        {
            eat(Token::Type::MINUS);
            res -= term();
        }
    }
    return std::to_string(res);
}

int Parser::factor()
{
    Token token = currentToken;
    if(token.getType() == Token::Type::INTEGER)
    {
        eat(Token::Type::INTEGER);
        return std::stoi(token.getValue());
    }
    else if (token.getType() == Token::Type::LPAREN)
    {
        eat(Token::Type::LPAREN);
        int result = std::stoi(expr());
        eat(Token::Type::RPAREN);
        return result;
    }
    throw(std::runtime_error("error getting factor"));
}

Parser::Parser(Lex lex) : lex(lex)
{
    currentToken = this->lex.getNextToken();
}

int Parser::term()
{
    int res = factor();

    while(currentToken.getType() == Token::Type::MUL || currentToken.getType() == Token::Type::DIV)
    {
        Token token = currentToken;
        if(token.getType() == Token::Type::MUL)
        {
            eat(Token::Type::MUL);
            res *= factor();
        }
        else if(token.getType() == Token::Type::DIV)
        {
            eat(Token::Type::DIV);
            res /= factor();
        }
    }
    return res;
}
