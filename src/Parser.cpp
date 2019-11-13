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

BinNode* Parser::expr()
{
    BinNode* node = term();
    BinNode *newNode = nullptr;

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
        newNode = new BinNode(token);
        newNode->left = node;
        newNode->right = term();
    }
    return newNode == nullptr ? node : newNode;
}

BinNode* Parser::factor()
{
    Token token = currentToken;
    if(token.getType() == Token::PLUS)
    {
        eat(Token::PLUS);
        auto* node = new BinNode(Token(factor()->key.getValue(), Token::INTEGER, Token::PLUS));
        return node;
    }
    else if(token.getType() == Token::MINUS)
    {
        eat(Token::MINUS);
        auto* nextFactor = factor();
        if(nextFactor->key.getOp() == Token::MINUS)
            return new BinNode(Token(nextFactor->key.getValue(), Token::INTEGER, Token::PLUS));
        return new BinNode(Token(nextFactor->key.getValue(), Token::INTEGER, Token::MINUS));;
    }
    else if (token.getType() == Token::Type::INTEGER)
    {
        eat(Token::Type::INTEGER);
        return new BinNode(token);
    } else if (token.getType() == Token::Type::LPAREN)
    {
        eat(Token::Type::LPAREN);
        BinNode* node = expr();
        eat(Token::Type::RPAREN);
        return node;
    }
    else if (token.getType() == Token::ASSIGN)
    {
        eat(Token::ASSIGN);
        return new BinNode(token);
    } else if (token.getType() == Token::IDENTIFIER)
    {
        eat(Token::IDENTIFIER);
        return new BinNode(token);
    }

    throw (std::runtime_error("error getting factor"));
}

BinNode* Parser::term()
{
    BinNode* node = factor();
    BinNode* newNode = nullptr;

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
        newNode = new BinNode(token);
        newNode->left = node;
        newNode->right = factor();
    }
    return newNode == nullptr ? node : newNode;
}

BinNode* Parser::parse()
{
    return expr();
}
