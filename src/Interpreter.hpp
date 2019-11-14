//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_INTERPRETER_HPP
#define RATTLE_INTERPRETER_HPP

#include "Parser.hpp"
#include <unordered_map>
#include <functional>

class Interpreter
{
public:
    Interpreter(const Parser &parser);

    std::string interpret();

private:
    Parser parser;

    Token runTree(BinNode *tree);

    static bool doAsFloat(BinNode *tree);

    static bool doAsString(BinNode *tree);

    static std::unordered_map<std::string, Token> variables;
};


#endif //RATTLE_INTERPRETER_HPP
