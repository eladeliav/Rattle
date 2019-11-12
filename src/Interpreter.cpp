//
// Created by elade on 11/12/2019.
//

#include "Interpreter.hpp"

Interpreter::Interpreter(const Parser &parser) : parser(parser)
{}

std::string Interpreter::interpret()
{
    BinOp* tree = parser.parse();
    return runTree(tree);
}

std::string Interpreter::runTree(BinOp* tree)
{
    if(tree == nullptr)
        return "0";
    if(tree->key.getType() == Token::Type::PLUS)
    {
        int lVal = std::stoi(runTree(tree->left));
        int rVal = std::stoi(runTree(tree->right));
        return std::to_string(lVal + rVal);
    }
}
