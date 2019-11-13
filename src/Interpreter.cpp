//
// Created by elade on 11/12/2019.
//

#include "Interpreter.hpp"

std::unordered_map<std::string, std::string> Interpreter::variables;

Interpreter::Interpreter(const Parser &parser) : parser(parser)
{}

void printBT(const std::string& prefix, const BinNode* node, bool isLeft)
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

void printBT(const BinNode* node)
{
    printBT("", node, false);
}

std::string Interpreter::interpret()
{
    BinNode* tree = parser.parse();
    //printBT(tree);
    return runTree(tree);
}

std::string Interpreter::runTree(BinNode* tree)
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
        case Token::FLOAT:
            if(tree->key.getOp() == Token::END_OF_LINE)
                return tree->key.getValue();
            else
                return tree->key.getOp() == Token::PLUS ? tree->key.getValue() : std::to_string(-1 * std::stof(tree->key.getValue()));
        case Token::PLUS:
            if(tree->left->key.getType() == Token::FLOAT || tree->right->key.getType() == Token::FLOAT)
            {
                float lValf = std::stof(runTree(tree->left));
                float rValf = std::stof(runTree(tree->right));
                return std::to_string(lValf + rValf);
            }
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal + rVal);
        case Token::MINUS:
            if(tree->left->key.getType() == Token::FLOAT || tree->right->key.getType() == Token::FLOAT)
            {
                float lValf = std::stof(runTree(tree->left));
                float rValf = std::stof(runTree(tree->right));
                return std::to_string(lValf - rValf);
            }
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal - rVal);
        case Token::MUL:
            if(tree->left->key.getType() == Token::FLOAT || tree->right->key.getType() == Token::FLOAT)
            {
                float lValf = std::stof(runTree(tree->left));
                float rValf = std::stof(runTree(tree->right));
                return std::to_string(lValf * rValf);
            }
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal * rVal);
        case Token::DIV:
            if(tree->left->key.getType() == Token::FLOAT || tree->right->key.getType() == Token::FLOAT)
            {
                float lValf = std::stof(runTree(tree->left));
                float rValf = std::stof(runTree(tree->right));
                return std::to_string(lValf / rValf);
            }
            lVal = std::stoi(runTree(tree->left));
            rVal = std::stoi(runTree(tree->right));
            return std::to_string(lVal / rVal);
        case Token::ASSIGN:
        {
            std::string id = tree->left->key.getValue();
            std::string val = runTree(tree->right);
            if(variables.find(val) != variables.end())
            {
                variables[id] = variables[val];
            }
            else
            {

                variables[id] = val;
            }
            return variables[id];
        }
        case Token::IDENTIFIER:
            return variables[tree->key.getValue()];
        case Token::PRINT:
        {
            return runTree(tree->right);
        }
        default:
            throw(std::runtime_error("Invalid tree"));
    }
}
