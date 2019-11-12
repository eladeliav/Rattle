//
// Created by elade on 11/12/2019.
//

#include "Interpreter.hpp"

Interpreter::Interpreter(const Parser &parser) : parser(parser)
{}

void printBT(const std::string& prefix, const BinOp* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "\\-- " );

        // print the value of the node
        std::cout << node->key.getValue() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

void printBT(const BinOp* node)
{
    printBT("", node, false);
}

std::string Interpreter::interpret()
{
    BinOp* tree = parser.parse();
    printBT(tree);
    return runTree(tree);
}

std::string Interpreter::runTree(BinOp* tree)
{
    if(tree == nullptr)
        return "0";

    int lVal = 0;
    int rVal = 0;

    switch(tree->key.getType())
    {
        case Token::INTEGER:
            if(tree->key.getOp() == Token::END_OF_LINE)
                return tree->key.getValue();
            else
                return tree->key.getOp() == Token::PLUS ? tree->key.getValue() : std::to_string(-1 * std::stoi(tree->key.getValue()));
        case Token::PLUS:
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal + rVal);
        case Token::MINUS:
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal - rVal);
        case Token::MUL:
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal * rVal);
        case Token::DIV:
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal / rVal);
        default:
            throw(std::runtime_error("Invalid tree"));
    }
}
