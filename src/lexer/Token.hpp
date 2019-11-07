//
// Created by elade on 11/6/2019.
//

#ifndef RATTLE_TOKEN_HPP
#define RATTLE_TOKEN_HPP
#include <iostream>
#include <string>
namespace Lexer
{

    class Token
    {
    public:

        enum Type
        {
            INTEGER,
            ADD,
            SUB,
            END_OF_LINE
        };

        Token () = default;

        Token (const std::string& value, Type type) : value(value), type(type) {}

        const std::string &getValue() const
        {
            return value;
        }

        Type getType() const
        {
            return type;
        }

    private:
        std::string value;
        Type type;
    };

};


#endif //RATTLE_TOKEN_HPP
