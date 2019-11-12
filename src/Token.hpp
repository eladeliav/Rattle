//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_TOKEN_HPP
#define RATTLE_TOKEN_HPP

#include <iostream>
#include <string>
#include <unordered_map>

#define INTEGER_REGEX "^[0-9]*$"
#define PLUS_REGEX "[+]"
#define MINUS_REGEX "[-]"
#define MUL_REGEX "[*]"
#define DIV_REGEX "[/]"
#define LPAREN_REGEX "[(]"
#define RPAREN_REGEX "[)]"
#define END_OF_LINE_REGEX "[\n]"

class Token
{
public:

    enum Type
    {
        INTEGER,
        PLUS,
        MINUS,
        MUL,
        DIV,
        LPAREN,
        RPAREN,
        END_OF_LINE
    };

    Token() = default;

    Token(Type type, const std::string &value) : value(value), type(type)
    {
        op = END_OF_LINE;
    }

    Token(const std::string &value, Type type, Type op) : value(value), type(type), op(op)
    {}

    const std::string &getValue() const
    {
        return value;
    }

    Type getType() const
    {
        return type;
    }

    Type getOp() const
    {
        return op;
    }

private:
    std::string value;
    Type type;
    Type op;
};

const std::unordered_map<Token::Type, std::string> TYPE_CHARS =
        {
                {Token::Type::INTEGER,     INTEGER_REGEX},
                {Token::Type::PLUS,        PLUS_REGEX},
                {Token::Type::MINUS,       MINUS_REGEX},
                {Token::Type::MUL,         MUL_REGEX},
                {Token::Type::DIV,         DIV_REGEX},
                {Token::Type::LPAREN,      LPAREN_REGEX},
                {Token::Type::RPAREN,      RPAREN_REGEX},
                {Token::Type::END_OF_LINE, END_OF_LINE_REGEX},

        };


#endif //RATTLE_TOKEN_HPP
