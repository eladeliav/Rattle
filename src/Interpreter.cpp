//
// Created by elade on 11/12/2019.
//

#include "Interpreter.hpp"

std::unordered_map<std::string, Token> Interpreter::variables;

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
    return runTree(tree).getValue();
}

Token Interpreter::runTree(BinNode* tree)
{
    if(tree == nullptr)
        return Token("", Token::END_OF_LINE);

    int lVal = 0;
    int rVal = 0;

    switch(tree->key.getType())
    {
        case Token::INTEGER:
            if(tree->key.getOp() == Token::MINUS)
            {
                return Token(std::to_string(std::stoi(tree->key.getValue()) * -1), Token::INTEGER);
            }
            return tree->key;
        case Token::FLOAT:
            if(tree->key.getOp() == Token::MINUS)
            {
                return Token(std::to_string(std::stof(tree->key.getValue()) * -1.0), Token::FLOAT);
            }
            return tree->key;
        case Token::PLUS:
            if(doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf + rValf), Token::FLOAT);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal + rVal), Token::INTEGER);
        case Token::MINUS:
            if(doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf - rValf), Token::FLOAT);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal - rVal), Token::INTEGER);
        case Token::MUL:
            if(doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf * rValf), Token::FLOAT);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal * rVal), Token::INTEGER);
        case Token::DIV:
            if(doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf / rValf), Token::FLOAT);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal / rVal), Token::INTEGER);
        case Token::ASSIGN:
        {
            std::string id = tree->left->key.getValue();
            Token val = runTree(tree->right);
            if(variables.find(val.getValue()) != variables.end())
            {
                variables[id] = variables[val.getValue()];
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
        case Token::PRINT_TYPE:
            return Token(TYPE_TO_STRINGS.at(runTree(tree->right).getType()), Token::END_OF_LINE);
        default:
            throw(std::runtime_error("Invalid tree"));
    }
}

bool Interpreter::doAsFloat(BinNode *tree)
{
    return tree->left->key.getType() == Token::FLOAT || tree->right->key.getType() == Token::FLOAT ||
           variables[tree->left->key.getValue()].getType() == Token::FLOAT ||
           variables[tree->right->key.getValue()].getType() == Token::FLOAT;
}
