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
    }
    else if(token.getType() == Token::IDENTIFIER)
    {
        eat(token.getType());
        if(currentToken.getType() != Token::LPAREN)
            return new BinNode(token);
        // it's a function call
        eat(Token::LPAREN);
        auto* funcNode = new FunctionNode(token);
        while(currentToken.getType() != Token::RPAREN)
        {
            funcNode->localScope.push_back(expr());
            if(currentToken.getType() == Token::COMMA)
                eat(Token::COMMA);
        }
        eat(Token::RPAREN);
        return funcNode;
    }
    else if (token.getType() == Token::MINUS)
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
    } else if (BUILT_IN_FUNCTIONS.find(currentToken.getType()) != BUILT_IN_FUNCTIONS.end())
    {
        eat(token.getType());
        BinNode *e = expr();
        auto *node = new BinNode(token);
        node->right = e;
        return node;
    }
    else if (token.getType() == Token::RETURN)
    {
        token.setOp(Token::RETURN);
        eat(token.getType());
        BinNode *e = expr();
        auto *node = new BinNode(token);
        node->right = e;
        return node;
    }
    else if(token.getType() == Token::IF)
    {
        eat(token.getType());
        BinNode *condition = expr();
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
        BinNode *condition = expr();
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
    else if(token.getType() == Token::DEF)
    {
        eat(token.getType());
        auto* funcNode = new FunctionNode(Token(currentToken.getValue(), Token::DEF));
        eat(currentToken.getType());
        eat(Token::LPAREN);
        while(currentToken.getType() != Token::RPAREN)
        {
            if(currentToken.getType() != Token::IDENTIFIER)
                throw std::runtime_error("Expected identifier token");

            funcNode->localScope.push_back(new BinNode(currentToken));
            eat(currentToken.getType());
            if(currentToken.getType() == Token::COMMA)
                eat(Token::COMMA);
        }
        eat(Token::RPAREN);
        eat(currentToken.getType());
        eat(currentToken.getType());
        auto* blockNode = getBlock();
        funcNode->left = blockNode;
        return funcNode;
    }
    eat(token.getType());
    return new BinNode(token);
}


BlockNode *Parser::getBlock()
{
    auto* blockNode = new BlockNode(Token("", Token::BLOCK));

    while(currentToken.getType() != Token::RBRACE)
    {
        BinNode* e = expr();
        e->key.setOp(Token::BLOCK);
        blockNode->block.push_back(e);
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
