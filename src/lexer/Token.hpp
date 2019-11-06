//
// Created by elad on 06/11/2019.
//

#ifndef RATTLE_TOKEN_HPP
#define RATTLE_TOKEN_HPP

#include <unordered_set>
#include <iostream>
#include <string>


namespace Lexer
{
    class Token
    {
    public:
        enum class Type
        {
            IDENTIFIER,
            KEYWORD,
            STRING,
            LITERAL,
            COMMENT,
            OPERATOR,
            DELIMINATOR,
            WHITESPACE,
            NEWLINE
        };


    private:
        std::string value;
        Type tokenType;
        std::string typeName;
    public:

        Token() = default;

        Token(const Token &token) : value(token.value), tokenType(token.tokenType)
        { /* empty */ }

        Token(const std::string tokenValue_, Type tokenType_, const std::string typeName_) : value{tokenValue_},
                                                                                             tokenType{tokenType_},
                                                                                             typeName{typeName_}
        {
        }

        Type getTokenType() const
        { return tokenType; }

        std::string getValue() const
        {
            return value;
        }

        std::string getTypeName() const
        {
            return typeName;
        }
    };

};


#endif //RATTLE_TOKEN_HPP
