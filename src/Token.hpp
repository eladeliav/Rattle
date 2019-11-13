//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_TOKEN_HPP
#define RATTLE_TOKEN_HPP

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>

#define INTEGER_REGEX "^[0-9]*$"
#define FLOAT_REGEX "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$"
#define PLUS_REGEX "[+]"
#define MINUS_REGEX "[-]"
#define MUL_REGEX "[*]"
#define DIV_REGEX "[/]"
#define LPAREN_REGEX "[(]"
#define RPAREN_REGEX "[)]"
#define END_OF_LINE_REGEX "[\n]"
#define IDENTIFIER_REGEX "[_a-zA-Z][_a-zA-Z0-9]{0,30}"
#define ASSIGN_REGEX "[=]"
#define PRINT_REGEX "(?:^|\\W)print(?:$|\\W)"

class Token
{
public:

    enum Type
    {
        INTEGER,
        FLOAT,
        PLUS,
        MINUS,
        MUL,
        DIV,
        LPAREN,
        RPAREN,
        IDENTIFIER,
        ASSIGN,
        PRINT,
        XOR,
        AND,
        END_OF_LINE
    };

    Token() = default;

    Token(Type type, const std::string &value) : value(value), type(type)
    {
        op = END_OF_LINE;
    }

    Token(const std::string &value, Type type, Type op) : value(value), type(type), op(op)
    {}

    Token(const Token &other)
    {
        value = other.value;
        type = other.type;
        op = other.op;
    }

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

    friend std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << "{value: " << token.value << " type: " << token.type << " op: " << token.op << "}";
        return os;
    }

private:
    std::string value;
    Type type;
    Type op;
};

const std::map<Token::Type, std::string> TYPE_CHARS =
        {
                {Token::Type::INTEGER,     INTEGER_REGEX},
                {Token::Type::FLOAT,       FLOAT_REGEX},
                {Token::Type::PLUS,        PLUS_REGEX},
                {Token::Type::MINUS,       MINUS_REGEX},
                {Token::Type::MUL,         MUL_REGEX},
                {Token::Type::DIV,         DIV_REGEX},
                {Token::Type::LPAREN,      LPAREN_REGEX},
                {Token::Type::RPAREN,      RPAREN_REGEX},
                {Token::PRINT,             PRINT_REGEX},
                {Token::Type::END_OF_LINE, END_OF_LINE_REGEX},
                {Token::ASSIGN,            ASSIGN_REGEX},
                {Token::IDENTIFIER,        IDENTIFIER_REGEX}
        };

const std::unordered_set<Token::Type> OPERATOR_TYPES = {
        Token::PLUS, Token::MINUS, Token::MUL, Token::DIV, Token::ASSIGN
};


#endif //RATTLE_TOKEN_HPP
