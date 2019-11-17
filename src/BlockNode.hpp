//
// Created by elade on 11/17/2019.
//

#ifndef RATTLE_BLOCKNODE_HPP
#define RATTLE_BLOCKNODE_HPP

#include "BinNode.hpp"
#include <vector>

class BlockNode : public BinNode
{
public:
    explicit BlockNode(const Token &key) : BinNode(key)
    {
    }

    std::vector<BinNode *> block;

};

#endif //RATTLE_BLOCKNODE_HPP
