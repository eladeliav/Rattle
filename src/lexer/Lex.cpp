//
// Created by elade on 11/6/2019.
//

#include "Lex.hpp"

Lexer::Lex::Lex(const std::string &text) : text(text)
{
    currentChar = text[pos];
}

void Lexer::Lex::advance()
{
    this->pos++;
    if((size_t) pos > text.size() - 1)
        currentChar = '\0';
    else
        currentChar = text[pos];
}

void Lexer::Lex::skip_whitespaces()
{
    while(currentChar != '\0' && std::isspace(currentChar))
        advance();
}

int Lexer::Lex::getNextInteger()
{
    std::string sResult;
    while(currentChar != '\0' && std::isdigit(currentChar))
    {
        sResult += currentChar;
        advance();
    }
    return std::stoi(sResult);
}

Lexer::Token Lexer::Lex::getNextToken()
{
    while(currentChar != '\0')
    {
        if(std::isspace(currentChar))
        {
            skip_whitespaces();
            continue;
        }


        for(const auto& r : TYPE_CHARS)
        {
            std::regex reg(r.second);
            std::string strChar(1, currentChar);

            if(std::regex_match(strChar, reg))
            {
                if(r.first == Token::Type::INTEGER)
                    return Token(r.first, std::to_string(getNextInteger()));
                advance();
                return Token(r.first, strChar);
            }
        }

        throw(std::runtime_error("Parsing error"));

    }
    return Token(Token::Type::END_OF_LINE, "\0");
}
