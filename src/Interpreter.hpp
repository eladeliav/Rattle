//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_INTERPRETER_HPP
#define RATTLE_INTERPRETER_HPP

#include "Parser.hpp"
#include <unordered_map>
#include <functional>
#include <stack>

class Interpreter
{
public:
    Interpreter(const Parser &parser);

    std::string interpret();

private:
    Parser parser;

    Token runTree(BinNode *tree);

    Token doMathOperator(BinNode* tree);

    Token doCompareOperator(BinNode* tree);

    Token doBuiltInFunctions(BinNode* tree);

    static bool doAsFloat(BinNode *tree);

    static bool doAsString(BinNode *tree);

    static std::unordered_map<std::string, Token> variables;
    static std::unordered_map<std::string, Token> currentScope;
    static std::stack<std::unordered_map<std::string, Token>> scopes;
    static std::unordered_map<std::string, FunctionNode*> functions;
};


#endif //RATTLE_INTERPRETER_HPP
