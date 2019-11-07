//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_LEXER_HPP
#define RATTLE_LEXER_HPP

#include "Token.hpp"
#include <string>
#include <regex>

#define INTEGER_REGEX "^[0-9]*$"

namespace Lexer
{
    class Lex
    {
    public:
        Lex() = default;
        Lex(std::string _text) : text(_text), currentChar(_text[pos]) {}

        std::string runExpression();

    private:
        std::string text;
        int pos = 0;
        Token currentToken;
        char currentChar;
    private:
        Token getNextToken();
        void eat(Token::Type type);
    };

};


#endif //RATTLE_LEXER_HPP
