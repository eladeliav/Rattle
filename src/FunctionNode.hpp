//
// Created by elade on 11/20/2019.
//

#ifndef RATTLE_FUNCTIONNODE_HPP
#define RATTLE_FUNCTIONNODE_HPP

#include "BinNode.hpp"
#include "Token.hpp"
#include "BlockNode.hpp"
#include <vector>

class FunctionNode : public BinNode
{
public:
    explicit FunctionNode(const Token &key) : BinNode(key)
    {
    }

    std::vector<Token> localScope;

};

#endif //RATTLE_FUNCTIONNODE_HPP
