//
// Created by elade on 11/6/2019.
//

#include "Lexer.hpp"

Lexer::Lexer(const std::string &text) : text(text)
{
    currentChar = text[pos];
}

void Lexer::advance()
{
    this->pos++;
    if((size_t) pos > text.size() - 1)
        currentChar = '\0';
    else
        currentChar = text[pos];
}

void Lexer::skip_whitespaces()
{
    while(currentChar != '\0' && std::isspace(currentChar))
        advance();
}

Token Lexer::getNextNumber()
{
    std::string sResult;
    while(currentChar != '\0' && std::isdigit(currentChar))
    {
        sResult += currentChar;
        advance();
    }

    if(currentChar == '.')
    {
        sResult += currentChar;
        advance();
        while(currentChar != '\0' && std::isdigit(currentChar))
        {
            sResult += currentChar;
            advance();
        }
        return Token(sResult, Token::FLOAT);
    }

    return Token(sResult, Token::INTEGER);
}

Token Lexer::getNextId()
{
    std::string sResult;
    while(currentChar != '\0' && std::isalnum(currentChar))
    {
        sResult += currentChar;
        advance();
    }

    for(auto const& p : TYPE_CHARS)
    {
        std::regex reg(p.second);
        if(p.first == Token::IDENTIFIER)
            continue;
        if(std::regex_match(sResult, reg))
        {
            return Token(sResult, p.first);
        }
    }

    Token token(sResult, Token::IDENTIFIER);
    return token;
}

Token Lexer::getNextToken()
{
    while(currentChar != '\0')
    {
        if(std::isspace(currentChar))
        {
            skip_whitespaces();
            continue;
        }

        if(std::isalpha(currentChar))
        {
            return getNextId();
        }

        for(const auto& r : TYPE_CHARS)
        {
            std::regex reg(r.second);
            std::string strChar(1, currentChar);

            if(std::regex_match(strChar, reg))
            {
                if(r.first == Token::Type::INTEGER || r.first == Token::Type::FLOAT)
                    return getNextNumber();
                advance();
                return Token(strChar, r.first);
            }
        }

        throw(std::runtime_error("Parsing error"));

    }
    return Token("\0", Token::Type::END_OF_LINE);
}
