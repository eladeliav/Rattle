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
    template<class T>
    class Classifier
    {
    public:
        Classifier(Token::Type type, std::string name, std::unordered_set<T> tokens) :
                type{type},
                name{name},
                tokens{tokens}
        {}

        bool among(const T &word) const
        {
            return tokens.find(word) != tokens.end();
        }

        Token::Type getType() const
        { return type; }

        std::string getTypeName() const
        { return name; };


    private:

        Token::Type type;
        std::string name;
        std::unordered_set<T> tokens;
    };

    const std::vector<Classifier<std::string>> string_classifiers{
            {Token::Type::KEYWORD,     "Keyword",     {"var", "for", "while", "print", "const"}},
            {Token::Type::OPERATOR,    "Operator",    {"+", "-", "/", "=", "*", "==", "!=", "+=", "-=", "*=", "/=", "--", "++"}},
    };

    const std::vector<Classifier<char>> char_classifiers{
            {Token::Type::OPERATOR,    "Operator",    {'+', '-', '*', '/', '='}},
            {Token::Type::NEWLINE,     "New Line",    {'\n',  '\r',  '\t'}},
            {Token::Type::WHITESPACE,  "White Space", {'\n',  '\r',  '\t',    ' '}},
            {Token::Type::DELIMINATOR, "Deliminator", {'(',   ')',   ';', '{', '}', '[', ']'}}
    };

};

#endif //RATTLE_CLASSIFIER_HPP
