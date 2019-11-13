//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_INTERPRETER_HPP
#define RATTLE_INTERPRETER_HPP
#include "Parser.hpp"
#include <unordered_map>

class Interpreter
{
public:
    Interpreter(const Parser &parser);
    std::string interpret();
private:
    Parser parser;
    std::string runTree(BinNode* tree);
    static std::unordered_map<std::string, std::string> variables;
};


#endif //RATTLE_INTERPRETER_HPP
