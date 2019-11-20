//
// Created by elade on 11/20/2019.
//

#ifndef RATTLE_IFNODE_HPP
#define RATTLE_IFNODE_HPP

#include "BinNode.hpp"
#include "BlockNode.hpp"
#include <vector>

class IfNode : public BinNode
{
public:
    explicit IfNode(const Token &key) : BinNode(key)
    {
    }

    std::vector<BinNode*> elseIfs;
    BlockNode* elseBlock = nullptr;

};

#endif //RATTLE_IFNODE_HPP
