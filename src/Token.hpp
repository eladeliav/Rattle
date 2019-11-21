//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_TOKEN_HPP
#define RATTLE_TOKEN_HPP

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <utility>

#define INTEGER_REGEX "^[0-9]*$"
#define FLOAT_REGEX "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$"
#define STRING_REGEX "\"([^\\\"]|\\.)*\""
#define PLUS_REGEX "[+]"
#define MINUS_REGEX "[-]"
#define MUL_REGEX "[*]"
#define DIV_REGEX "[/]"
#define LPAREN_REGEX "[(]"
#define RPAREN_REGEX "[)]"
#define LBRACE_REGEX "[{]"
#define RBRACE_REGEX "[}]"
#define END_OF_LINE_REGEX "[\n]"
#define IDENTIFIER_REGEX "[_a-zA-Z][_a-zA-Z0-9]{0,30}"
#define ASSIGN_REGEX "[=]"
#define COMPARE_EQUAL_REGEX "=="
#define COMPARE_NOT_EQUAL_REGEX "!="
#define IF_AND_REGEX "&&"
#define IF_OR_REGEX "||"
#define LESS_THAN_REGEX "<"
#define LESS_THAN_EQUAL_REGEX "<="
#define GREATER_THAN_REGEX ">"
#define IF_NOT_REGEX "!"
#define COMMA_REGEX ","
#define GREATER_THAN_EQUAL_REGEX ">="
#define PRINT_REGEX "(?:^|\\W)print(?:$|\\W)"
#define PRINT_TYPE_REGEX "(?:^|\\W)type(?:$|\\W)"
#define BOOL_REGEX "(?:^|\\W)true|false(?:$|\\W)"
#define ELSE_REGEX "(?:^|\\W)else(?:$|\\W)"
#define ELIF_REGEX "(?:^|\\W)else if(?:$|\\W)"
#define INPUT_REGEX "(?:^|\\W)input(?:$|\\W)"
#define DEF_REGEX "(?:^|\\W)def(?:$|\\W)"
#define WHILE_REGEX "(?:^|\\W)while(?:$|\\W)"
#define RETURN_REGEX "(?:^|\\W)return(?:$|\\W)"
#define INT_CAST_REGEX "(?:^|\\W)int(?:$|\\W)"
#define STRING_CAST_REGEX "(?:^|\\W)string(?:$|\\W)"
#define FLOAT_CAST_REGEX "(?:^|\\W)float(?:$|\\W)"
#define TRUE "true"
#define FALSE "false"
#define IF_REGEX "(?:^|\\W)if(?:$|\\W)"

class Token
{
public:

    enum Type
    {
        INTEGER,
        FLOAT,
        STRING,
        BOOL,
        PLUS,
        MINUS,
        MUL,
        DIV,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        IDENTIFIER,
        IF,
        ELSE,
        ELIF,
        INPUT,
        WHILE,
        DEF,
        COMMA,
        RETURN,
        ASSIGN,
        COMPARE_EQUAL,
        COMPARE_NOT_EQUAL,
        LESS_THAN,
        LESS_THAN_EQUAL,
        GREATER_THAN,
        GREATER_THAN_EQUAL,
        IF_AND,
        IF_OR,
        IF_NOT,
        PRINT,
        PRINT_TYPE,
        BLOCK,
        INT_CAST,
        STRING_CAST,
        FLOAT_CAST,
        END_OF_FILE,
        END_OF_LINE
    };

    Token() = default;

    Token(std::string value, Type type) : value(std::move(value)), type(type)
    {
        op = END_OF_LINE;
    }

    Token(std::string value, Type type, Type op) : value(std::move(value)), type(type), op(op)
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

    void setType(Type type)
    {
        Token::type = type;
    }

    void setValue(const std::string &value)
    {
        Token::value = value;
    }

    void setOp(Type op)
    {
        Token::op = op;
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
                {Token::Type::INTEGER, INTEGER_REGEX},
                {Token::Type::FLOAT, FLOAT_REGEX},
                {Token::Type::STRING, STRING_REGEX},
                {Token::BOOL, BOOL_REGEX},
                {Token::Type::PLUS, PLUS_REGEX},
                {Token::Type::MINUS, MINUS_REGEX},
                {Token::Type::MUL, MUL_REGEX},
                {Token::IF, IF_REGEX},
                {Token::ELSE, ELSE_REGEX},
                {Token::ELIF, ELIF_REGEX},
                {Token::INPUT, INPUT_REGEX},
                {Token::DEF, DEF_REGEX},
                {Token::WHILE, WHILE_REGEX},
                {Token::COMMA, COMMA_REGEX},
                {Token::RETURN, RETURN_REGEX},
                {Token::Type::DIV, DIV_REGEX},
                {Token::Type::LPAREN, LPAREN_REGEX},
                {Token::Type::RPAREN, RPAREN_REGEX},
                {Token::Type::LBRACE, LBRACE_REGEX},
                {Token::Type::RBRACE, RBRACE_REGEX},
                {Token::PRINT, PRINT_REGEX},
                {Token::PRINT_TYPE, PRINT_TYPE_REGEX},
                {Token::Type::END_OF_LINE, END_OF_LINE_REGEX},
                {Token::COMPARE_EQUAL, COMPARE_EQUAL_REGEX},
                {Token::COMPARE_NOT_EQUAL, COMPARE_NOT_EQUAL_REGEX},
                {Token::LESS_THAN, LESS_THAN_REGEX},
                {Token::LESS_THAN_EQUAL, LESS_THAN_EQUAL_REGEX},
                {Token::GREATER_THAN, GREATER_THAN_REGEX},
                {Token::GREATER_THAN_EQUAL, GREATER_THAN_EQUAL_REGEX},
                {Token::ASSIGN, ASSIGN_REGEX},
                {Token::IDENTIFIER, IDENTIFIER_REGEX},
                {Token::IF_AND, IF_AND_REGEX},
                {Token::IF_OR, IF_OR_REGEX},
                {Token::INT_CAST, INT_CAST_REGEX},
                {Token::STRING_CAST, STRING_CAST_REGEX},
                {Token::FLOAT_CAST, FLOAT_CAST_REGEX},
                {Token::IF_NOT, IF_NOT_REGEX}
        };

const std::map<Token::Type, std::string> TYPE_TO_STRINGS =
        {
                {Token::Type::INTEGER, "int"},
                {Token::Type::FLOAT,   "float"},
                {Token::Type::STRING,  "string"},
                {Token::Type::BOOL,    "bool"}
        };

const std::unordered_set<Token::Type> BUILT_IN_FUNCTIONS = {
        Token::PRINT, Token::PRINT_TYPE, Token::INT_CAST, Token::STRING_CAST, Token::FLOAT_CAST, Token::INPUT
};

const std::unordered_set<Token::Type> COMPARE_OPERATORS = {
        Token::COMPARE_EQUAL, Token::GREATER_THAN, Token::GREATER_THAN_EQUAL, Token::LESS_THAN, Token::LESS_THAN_EQUAL, Token::IF_AND, Token::IF_OR, Token::COMPARE_NOT_EQUAL, Token::IF_NOT
};

const std::unordered_set<Token::Type> LITERAL_TYPES = {
        Token::INTEGER, Token::FLOAT, Token::STRING, Token::BOOL
};

const std::unordered_set<Token::Type> MATH_OPERATORS = {
        Token::PLUS, Token::MINUS, Token::DIV, Token::MUL
};


#endif //RATTLE_TOKEN_HPP
