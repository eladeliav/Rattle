//
// Created by elade on 11/12/2019.
//

#include "Interpreter.hpp"

std::unordered_map<std::string, Token> Interpreter::variables;

Interpreter::Interpreter(const Parser &parser) : parser(parser)
{}

void printBT(const std::string &prefix, const BinNode *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "\\-- ");

        // print the value of the node
        std::cout << node->key.getValue() << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

void printBT(const BinNode *node)
{
    printBT("", node, false);
}

std::string Interpreter::interpret()
{
    BinNode *tree = parser.parse();
    //printBT(tree);
    auto* ptr = tree;
    while(ptr->key.getType() != Token::END_OF_FILE)
    {
        runTree(ptr);
        ptr = ptr->nextLine;
    }
    return "";
}

Token Interpreter::runTree(BinNode *tree)
{
    if (tree == nullptr)
        return Token("", Token::END_OF_LINE);

    int lVal = 0;
    int rVal = 0;

    switch (tree->key.getType())
    {
        case Token::INTEGER:
            if (tree->key.getOp() == Token::MINUS)
            {
                return Token(std::to_string(std::stoi(tree->key.getValue()) * -1), Token::INTEGER);
            }
            return tree->key;
        case Token::FLOAT:
            if (tree->key.getOp() == Token::MINUS)
            {
                return Token(std::to_string(std::stof(tree->key.getValue()) * -1.0), Token::FLOAT);
            }
            return tree->key;
        case Token::STRING:
            return tree->key;
        case Token::BOOL:
            return tree->key;
        case Token::PLUS:
            if (doAsString(tree))
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                return Token(lVals + rVals, Token::STRING);
            }
            else if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf + rValf), Token::FLOAT);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal + rVal), Token::INTEGER);
        case Token::MINUS:
            if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf - rValf), Token::FLOAT);
            } else if (doAsString(tree))
            {
                return Token("Cannot subtract strings", Token::END_OF_LINE);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal - rVal), Token::INTEGER);
        case Token::MUL:
            if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf * rValf), Token::FLOAT);
            } else if (doAsString(tree))
            {
                return Token("Cannot multiply strings", Token::END_OF_LINE);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal * rVal), Token::INTEGER);
        case Token::DIV:
            if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf / rValf), Token::FLOAT);
            } else if (doAsString(tree))
            {
                return Token("Cannot divide strings", Token::END_OF_LINE);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal / rVal), Token::INTEGER);
        case Token::ASSIGN:
        {
            std::string id = tree->left->key.getValue();
            Token val = runTree(tree->right);
            if (variables.find(val.getValue()) != variables.end())
            {
                variables[id] = variables[val.getValue()];
            } else
            {
                variables[id] = val;
            }
            return variables[id];
        }
        case Token::IDENTIFIER:
            return variables.find(tree->key.getValue()) != variables.end() ? variables[tree->key.getValue()] : Token(
                    "Variable not found", Token::END_OF_LINE);
        case Token::PRINT:
        {
            Token val = runTree(tree->right);
            std::cout << val.getValue() << std::endl;
            return val;
        }
        case Token::PRINT_TYPE:
        {
            Token token = runTree(tree->right);
            return token.getType() == Token::END_OF_LINE ? token : Token(
                    TYPE_TO_STRINGS.at(runTree(tree->right).getType()), Token::END_OF_LINE);
        }
        case Token::COMPARE_EQUAL:
        {
            if (doAsString(tree))
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals == rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            else if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf == rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal == rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::LESS_THAN:
        {
            if (doAsString(tree))
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals < rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            else if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf < rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal < rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::LESS_THAN_EQUAL:
        {
            if (doAsString(tree))
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals <= rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf <= rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal <= rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::GREATER_THAN:
        {
            if (doAsString(tree))
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals > rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf > rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }

            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal > rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::GREATER_THAN_EQUAL:
        {
            if (doAsString(tree))
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals >= rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsFloat(tree))
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf >= rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            lVal = std::stoi(runTree(tree->left).getValue());
            rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal >= rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::IF:
        {
            Token conditionBool = runTree(tree->left);
            if (conditionBool.getValue() == TRUE)
                return runTree(tree->right);
            return Token("", Token::END_OF_LINE);
        }
        case Token::BLOCK:
        {
            auto* ca = (BlockNode*)tree;
            for(BinNode* currentExpr : ca->block)
            {
                runTree(currentExpr);
            }
            return Token("", Token::END_OF_LINE);
        }
        case Token::END_OF_FILE:
        {
            return Token("", Token::END_OF_FILE);
        }
        case Token::END_OF_LINE:
        {
            return Token("", Token::END_OF_LINE);
        }
        default:
            throw (std::runtime_error("Invalid tree"));
    }
}

bool Interpreter::doAsFloat(BinNode *tree)
{
    if (tree == nullptr)
        return false;

    if (tree->key.getType() == Token::FLOAT)
        return true;

    if (variables[tree->key.getValue()].getType() == Token::FLOAT)
        return true;

    bool stringInLeft = doAsString(tree->left);

    bool stringInRight = doAsString(tree->right);

    return stringInLeft || stringInRight;
}

bool Interpreter::doAsString(BinNode *tree)
{
    if (tree == nullptr)
        return false;

    if (tree->key.getType() == Token::STRING)
        return true;

    if (variables[tree->key.getValue()].getType() == Token::STRING)
        return true;

    bool stringInLeft = doAsString(tree->left);

    bool stringInRight = doAsString(tree->right);

    return stringInLeft || stringInRight;

}
