//
// Created by elade on 11/12/2019.
//

#include "Parser.hpp"

#include <memory>

void Parser::eat(Token::Type type)
{
    if (currentToken.getType() == type)
        currentToken = lex.getNextToken();
    else
        throw (std::runtime_error("Unexpected Token"));
}


Parser::Parser(Lexer lex) : lex(lex)
{
    currentToken = this->lex.getNextToken();
}

BinOp* Parser::expr()
{
    BinOp* node = factor();
    BinOp *newNode = nullptr;

    while (currentToken.getType() == Token::Type::PLUS || currentToken.getType() == Token::Type::MINUS)
    {
        Token token = currentToken;
        if (token.getType() == Token::Type::PLUS)
        {
            eat(Token::Type::PLUS);
        } else if (token.getType() == Token::Type::MINUS)
        {
            eat(Token::Type::MINUS);
        }
        newNode = new BinOp(token);
        newNode->left = node;
        newNode->right = factor();
    }
    return newNode;
}

BinOp* Parser::factor()
{
    Token token = currentToken;
    if (token.getType() == Token::Type::INTEGER)
    {
        eat(Token::Type::INTEGER);
        return new BinOp(token);
    } else if (token.getType() == Token::Type::LPAREN)
    {
        eat(Token::Type::LPAREN);
        BinOp* node = expr();
        eat(Token::Type::RPAREN);
        return node;
    }
    throw (std::runtime_error("error getting factor"));
}

BinOp* Parser::term()
{
    BinOp* node = factor();
    BinOp* newNode = nullptr;

    while (currentToken.getType() == Token::Type::MUL || currentToken.getType() == Token::Type::DIV)
    {
        Token token = currentToken;
        if (token.getType() == Token::Type::MUL)
        {
            eat(Token::Type::MUL);
        } else if (token.getType() == Token::Type::DIV)
        {
            eat(Token::Type::DIV);
        }
        newNode = new BinOp(token);
        newNode->left = node;
        newNode->right = factor();
    }
    return newNode;
}

BinOp* Parser::parse()
{
    return expr();
}
