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
    if ((size_t) pos > text.size() - 1)
        currentChar = '\0';
    else
        currentChar = text[pos];
}

char Lexer::peek()
{
    int newPos = pos + 1;
    if ((size_t) pos > text.size() - 1)
        return '\0';
    else
        return text[newPos];
}

void Lexer::skip_whitespaces()
{
    while (currentChar != '\0' && std::isspace(currentChar))
        advance();
}

Token Lexer::getNextNumber()
{
    std::string sResult;
    while (currentChar != '\0' && std::isdigit(currentChar))
    {
        sResult += currentChar;
        advance();
    }

    if (currentChar == '.')
    {
        sResult += currentChar;
        advance();
        while (currentChar != '\0' && std::isdigit(currentChar))
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

    while ((currentChar != '\0' && std::isalnum(currentChar)) || currentChar == '"')
    {
        sResult += currentChar;
        advance();
    }

    for (auto const &p : TYPE_CHARS)
    {
        std::regex reg(p.second);
        if (p.first == Token::IDENTIFIER)
            continue;
        if (std::regex_match(sResult, reg))
        {
            if (p.first == Token::STRING)
            {
                sResult.erase(0, 1);
                sResult.erase(sResult.size() - 1, 1);
            }
            return Token(sResult, p.first);
        }
    }

    Token token(sResult, Token::IDENTIFIER);
    return token;
}

Token Lexer::getNextToken()
{
    while (currentChar != '\0')
    {

        if(currentChar == '\n')
        {
            advance();
            return Token("\\n", Token::END_OF_LINE);
        }

        if (std::isspace(currentChar))
        {
            skip_whitespaces();
            continue;
        }

        if (currentChar == '"')
        {
            std::string sResult;
            advance();
            while (currentChar != '\0' && currentChar != '"')
            {
                sResult += currentChar;
                advance();
            }
            advance();

            return Token(sResult, Token::STRING);

        }

        if (std::isalpha(currentChar))
        {
            return getNextId();
        }

        if (currentChar == '=' && peek() == '=')
        {
            advance();
            advance();
            return Token("==", Token::COMPARE_EQUAL);
        }

        if (currentChar == '&' && peek() == '&')
        {
            advance();
            advance();
            return Token("==", Token::IF_AND);
        }

        if (currentChar == '|' && peek() == '|')
        {
            advance();
            advance();
            return Token("==", Token::IF_OR);
        }

        for (const auto &r : TYPE_CHARS)
        {
            std::regex reg(r.second);
            std::string strChar(1, currentChar);

            if (std::regex_match(strChar, reg))
            {
                if (r.first == Token::Type::INTEGER || r.first == Token::Type::FLOAT)
                    return getNextNumber();
                advance();
                return Token(strChar, r.first);
            }
        }

        throw (std::runtime_error("Parsing error"));

    }
    return Token("\0", Token::Type::END_OF_FILE);
}
