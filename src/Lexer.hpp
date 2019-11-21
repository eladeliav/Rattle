//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_LEXER_HPP
#define RATTLE_LEXER_HPP

#include "Token.hpp"
#include <string>
#include <regex>
#include <exception>
#include <regex>
#include <unordered_map>

class Lexer
{
private:
    std::string text;
    int pos = 0;
    char currentChar;
public:
    Lexer(const std::string &text);

    void advance();

    char peek();

    void skip_whitespaces();

    void skip_comments(bool multiLine);

    Token getNextNumber();

    Token getNextToken();

    Token getNextId();
};


#endif //RATTLE_LEXER_HPP
