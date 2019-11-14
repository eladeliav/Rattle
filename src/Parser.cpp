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

BinNode *Parser::expr()
{
    BinNode *node = term();

    while (currentToken.getType() == Token::Type::PLUS || currentToken.getType() == Token::Type::MINUS ||
           currentToken.getType() == Token::PRINT)
    {
        Token token = currentToken;
        if (token.getType() == Token::Type::PLUS)
        {
            eat(Token::Type::PLUS);
        } else if (token.getType() == Token::Type::MINUS)
        {
            eat(Token::Type::MINUS);
        } else if (token.getType() == Token::ASSIGN)
        {
            eat(Token::Type::ASSIGN);
        } else if (token.getType() == Token::PRINT)
        {
            eat(Token::Type::PRINT);
        }
        else if (token.getType() == Token::PRINT_TYPE)
        {
            eat(Token::Type::PRINT_TYPE);
        }
        auto *tempNode = new BinNode(node);
        node = new BinNode(token);
        node->left = tempNode;
        node->right = term();
    }

    if (currentToken.getType() == Token::ASSIGN)
    {
        Token token = currentToken;
        eat(Token::Type::ASSIGN);
        auto *tempNode = new BinNode(node);
        node = new BinNode(token);
        node->left = tempNode;
        node->right = expr();
    }

    return node;
}

BinNode *Parser::factor()
{
    Token token = currentToken;
    if (token.getType() == Token::PLUS)
    {
        eat(Token::PLUS);
        auto *node = new BinNode(Token(factor()->key.getValue(), Token::INTEGER, Token::PLUS));
        return node;
    } else if (token.getType() == Token::MINUS)
    {
        eat(Token::MINUS);
        auto *nextFactor = factor();
        if (nextFactor->key.getOp() == Token::MINUS)
            return new BinNode(Token(nextFactor->key.getValue(), Token::INTEGER, Token::PLUS));
        return new BinNode(Token(nextFactor->key.getValue(), Token::INTEGER, Token::MINUS));;
    } else if (token.getType() == Token::Type::INTEGER)
    {
        eat(Token::Type::INTEGER);
        return new BinNode(token);
    }
    else if (token.getType() == Token::Type::FLOAT)
    {
        eat(Token::Type::FLOAT);
        return new BinNode(token);
    }
    else if (token.getType() == Token::Type::LPAREN)
    {
        eat(Token::Type::LPAREN);
        BinNode *node = expr();
        eat(Token::Type::RPAREN);
        return node;
    } else if (token.getType() == Token::ASSIGN)
    {
        eat(Token::ASSIGN);
        return new BinNode(token);
    } else if (token.getType() == Token::IDENTIFIER)
    {
        eat(Token::IDENTIFIER);
        return new BinNode(token);
    } else if (token.getType() == Token::PRINT)
    {
        eat(Token::PRINT);
        eat(Token::Type::LPAREN);
        BinNode *e = expr();
        eat(Token::Type::RPAREN);
        auto *node = new BinNode(token);
        node->right = e;
        return node;
    }
    else if (token.getType() == Token::PRINT_TYPE)
    {
        eat(Token::PRINT_TYPE);
        eat(Token::Type::LPAREN);
        BinNode *e = expr();
        eat(Token::Type::RPAREN);
        auto *node = new BinNode(token);
        node->right = e;
        return node;
    }

    throw (std::runtime_error("error getting factor"));
}

BinNode *Parser::term()
{
    BinNode *node = factor();

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
        auto *tempNode = new BinNode(node);
        node = new BinNode(token);
        node->left = tempNode;
        node->right = term();
    }
    return node;
}

BinNode *Parser::parse()
{
    return expr();
}
