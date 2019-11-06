//
// Created by elad on 06/11/2019.
//

#ifndef RATTLE_CLASSIFIER_HPP
#define RATTLE_CLASSIFIER_HPP

#include "Token.hpp"
#include <string>
#include <vector>
#include <unordered_set>

namespace Lexer
{
    class Classifier
    {
    public:
        Classifier(Token::Type type, std::string name, std::unordered_set<std::string> tokens) :
                type{type},
                name{name},
                tokens{tokens}
        {}

        bool among(const std::string &word) const
        {
            if(type == Token::Type::WHITESPACE && word == "32")
            {
                return true;
            }
            if(type == Token::Type::DELIMINATOR && word == "59")
                return true;
            return tokens.find(word) != tokens.end();
        }

        Token::Type getType() const
        { return type; }

        std::string getTypeName() const
        { return name; };

    private:

        Token::Type type;
        std::string name;
        std::unordered_set<std::string> tokens;
    };

    static const std::vector<Classifier> classifiers{
            {Token::Type::KEYWORD,     "Keyword",     {"var", "for", "while", "print", "const"}},
            {Token::Type::OPERATOR,    "Operator",    {"+",   "-",   "*",     "/",     "=", "==", "!=", "+=", "-=", "*=", "/="}},
            {Token::Type::DELIMINATOR, "Deliminator", {"(",   ")",   ";"}},
            {Token::Type::NEWLINE,  "New Line",  {"\n",  "\r",  "\t"}},
            {Token::Type::WHITESPACE,  "White Space",  {"\n",  "\r",  "\t", " ", ""}},
    };

};

#endif //RATTLE_CLASSIFIER_HPP
