//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_LEX_HPP
#define RATTLE_LEX_HPP

#include "Token.hpp"
#include <string>
#include <regex>
#include <exception>
#include <regex>
#include <unordered_map>

namespace Lexer
{
    class Lex
    {
    private:
        std::string text;
        int pos = 0;
        char currentChar;
    public:
        Lex(const std::string &text);
        void advance();
        void skip_whitespaces();
        int getNextInteger();
        Token getNextToken();
    };

};


#endif //RATTLE_LEX_HPP
