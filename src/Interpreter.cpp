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
    auto *ptr = tree;
    while (ptr != nullptr && ptr->key.getType() != Token::END_OF_FILE)
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

    Token::Type type = tree->key.getType();

    if (MATH_OPERATORS.find(type) != MATH_OPERATORS.end())
    {
        return doMathOperator(tree);
    }

    if (LITERAL_TYPES.find(type) != LITERAL_TYPES.end())
    {
        if (type == Token::INTEGER)
        {
            if (tree->key.getOp() == Token::MINUS)
            {
                return Token(std::to_string(std::stoi(tree->key.getValue()) * -1), Token::INTEGER);
            }
            return tree->key;
        } else if (type == Token::FLOAT)
        {
            if (tree->key.getOp() == Token::MINUS)
            {
                return Token(std::to_string(std::stof(tree->key.getValue()) * -1.0), Token::FLOAT);
            }
            return tree->key;
        }
        return tree->key;
    }

    if(COMPARE_OPERATORS.find(type) != COMPARE_OPERATORS.end())
    {
        return doCompareOperator(tree);
    }

    switch (type)
    {
        case Token::IF:
        {
            Token conditionBool = runTree(tree->left);
            if (conditionBool.getValue() == TRUE)
                return runTree(tree->right);
            return Token("", Token::END_OF_LINE);
        }
        case Token::IDENTIFIER:
        {
            return variables.find(tree->key.getValue()) != variables.end() ? variables[tree->key.getValue()] : Token(
                    "Variable not found", Token::END_OF_LINE);
        }
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
        case Token::BLOCK:
        {
            auto *ca = (BlockNode *) tree;
            for (BinNode *currentExpr : ca->block)
            {
                runTree(currentExpr);
            }
            return Token("", Token::END_OF_LINE);
        }
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

Token Interpreter::doMathOperator(BinNode *tree)
{
    Token::Type type = tree->key.getType();
    bool doAsStr = doAsString(tree);
    bool doAsF = doAsFloat(tree);

    if (doAsStr && type != Token::PLUS)
        return Token("Cannot subtract strings", Token::END_OF_LINE);

    switch (type)
    {
        case Token::PLUS:
        {
            if (doAsStr)
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                return Token(lVals + rVals, Token::STRING);
            } else if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf + rValf), Token::FLOAT);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal + rVal), Token::INTEGER);
        }
        case Token::MINUS:
        {
            if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf - rValf), Token::FLOAT);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal - rVal), Token::INTEGER);
        }
        case Token::MUL:
        {
            if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf - rValf), Token::FLOAT);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal - rVal), Token::INTEGER);
        }
        case Token::DIV:
        {
            if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                return Token(std::to_string(lValf - rValf), Token::FLOAT);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            return Token(std::to_string(lVal - rVal), Token::INTEGER);
        }
        default:
            throw std::runtime_error("Expected a math operator");
    }
}

Token Interpreter::doCompareOperator(BinNode *tree)
{
    Token::Type type = tree->key.getType();
    bool doAsStr = doAsString(tree);
    bool doAsF = doAsFloat(tree);

    switch (type)
    {
        case Token::IF_AND:
        {
            bool left = runTree(tree->left).getValue() == TRUE;
            bool right = runTree(tree->right).getValue() == TRUE;
            if(left && right)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::IF_OR:
        {
            bool left = runTree(tree->left).getValue() == TRUE;
            bool right = runTree(tree->right).getValue() == TRUE;
            if(left || right)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::COMPARE_EQUAL:
        {
            if (doAsStr)
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals == rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf == rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal == rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::LESS_THAN:
        {
            if (doAsStr)
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals < rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf < rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal < rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::LESS_THAN_EQUAL:
        {
            if (doAsStr)
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals <= rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf <= rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal <= rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::GREATER_THAN:
        {
            if (doAsStr)
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals > rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf > rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal > rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        case Token::GREATER_THAN_EQUAL:
        {
            if (doAsStr)
            {
                std::string lVals = runTree(tree->left).getValue();
                std::string rVals = runTree(tree->right).getValue();
                if (lVals >= rVals)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            } else if (doAsF)
            {
                float lValf = std::stof(runTree(tree->left).getValue());
                float rValf = std::stof(runTree(tree->right).getValue());
                if (lValf >= rValf)
                    return Token("true", Token::BOOL);
                else
                    return Token("false", Token::BOOL);
            }
            int lVal = std::stoi(runTree(tree->left).getValue());
            int rVal = std::stoi(runTree(tree->right).getValue());
            if (lVal >= rVal)
                return Token("true", Token::BOOL);
            else
                return Token("false", Token::BOOL);
        }
        default:
            throw std::runtime_error("Expected a compare operator");
    }
}
