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
    } else if (token.getType() == Token::PRINT || token.getType() == Token::PRINT_TYPE || token.getType() == Token::INPUT)
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
        eat(currentToken.getType());
        eat(currentToken.getType());
        BlockNode* blockNode = getBlock();
        auto* node = new IfNode(Token("if", Token::IF));
        node->left = condition;
        node->right = blockNode;
        lastIf = node;
        return node;
    }
    else if(token.getType() == Token::ELIF)
    {
        eat(token.getType());
        eat(Token::Type::LPAREN);
        BinNode *condition = expr();
        eat(Token::Type::RPAREN);
        eat(currentToken.getType());
        eat(currentToken.getType());
        BlockNode* blockNode = getBlock();
        auto* node = new IfNode(Token("if", Token::IF));
        node->left = condition;
        node->right = blockNode;
        lastIf->elseIfs.push_back(node);
        return new BinNode();
    }
    else if(token.getType() == Token::ELSE)
    {
        eat(token.getType());
        eat(currentToken.getType());
        eat(currentToken.getType());
        auto* blockNode = getBlock();
        lastIf->elseBlock = blockNode;
        return new BinNode();
    }
    else if(token.getType() == Token::IF_NOT)
    {
        auto* node = new BinNode(currentToken);
        eat(token.getType());
        bool inParenthesis = false;
        if(currentToken.getType() == Token::LPAREN)
        {
            eat(Token::LPAREN);
            inParenthesis = true;
        }
        node->left = expr(); // condition
        if(currentToken.getType() == Token::RPAREN && inParenthesis)
            eat(Token::RPAREN);
        return node;
    }
    eat(token.getType());
    return new BinNode(token);
}


BlockNode *Parser::getBlock()
{
    auto* blockNode = new BlockNode(Token("", Token::BLOCK));

    while(currentToken.getType() != Token::RBRACE)
    {
        blockNode->block.push_back(expr());
        if(currentToken.getType() == Token::END_OF_LINE)
            eat(Token::END_OF_LINE);
    }
    if(currentToken.getType() == Token::RBRACE)
        eat(Token::RBRACE);
    return blockNode;
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
    auto* node = expr();
    auto* ptr = node;
    while (currentToken.getType() != Token::END_OF_FILE)
    {
        if(currentToken.getType() == Token::END_OF_LINE)
            eat(Token::END_OF_LINE);
        ptr->nextLine = expr();
        ptr = ptr->nextLine;
    }
    return node;
}
