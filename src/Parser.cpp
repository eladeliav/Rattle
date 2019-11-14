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
        eat(token.getType());
        auto *tempNode = new BinNode(node);
        node = new BinNode(token);
        node->left = tempNode;
        node->right = term();
    }

    if (currentToken.getType() == Token::ASSIGN || COMPARE_OPERATORS.find(currentToken.getType()) != COMPARE_OPERATORS.end())
    {
        Token token = currentToken;
        eat(token.getType());
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
    }
    else if (token.getType() == Token::Type::LPAREN)
    {
        eat(Token::Type::LPAREN);
        BinNode *node = expr();
        eat(Token::Type::RPAREN);
        return node;
    } else if (token.getType() == Token::PRINT || token.getType() == Token::PRINT_TYPE)
    {
        eat(token.getType());
        eat(Token::Type::LPAREN);
        BinNode *e = expr();
        eat(Token::Type::RPAREN);
        auto *node = new BinNode(token);
        node->right = e;
        return node;
    }
    else if(token.getType() == Token::IF)
    {
        eat(token.getType());
        eat(Token::Type::LPAREN);
        BinNode *condition = expr();
        eat(Token::Type::RPAREN);
        BinNode* ex = expr();
        auto *node = new BinNode(token);
        node->left = condition;
        node->right = ex;
        return node;
    }
    eat(token.getType());
    return new BinNode(token);
}

BinNode *Parser::term()
{
    BinNode *node = factor();

    while (currentToken.getType() == Token::Type::MUL || currentToken.getType() == Token::Type::DIV)
    {
        Token token = currentToken;
        eat(token.getType());
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
