//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_BINNODE_HPP
#define RATTLE_BINNODE_HPP

#include <iostream>
#include "Token.hpp"


class BinNode
{
public:
    BinNode()
    = default;


    BinNode(BinNode *pNode)
    {
        key = Token(pNode->key);
        if(pNode->left != nullptr)
            left = new BinNode(pNode->left->key);
        if(pNode->right != nullptr)
            right = new BinNode(pNode->right->key);
    }

    Token key;     ///< The key of the BinOp
    BinNode *left = nullptr;    ///< The left child of the BinOp
    BinNode *right = nullptr;   ///< The right child of the BinOp

    virtual ~BinNode()
    {
        std::cout << "destructor of binop" << std::endl;
    }

    /**
     * @brief Constructor of a binary search tree BinOp
     */
    BinNode(const Token key)
    {
        this->key = Token(key);
    }

    friend std::ostream &operator<<(std::ostream &os, const BinNode &node)
    {
        os << "key: " << node.key << " left: " << node.left << " right: " << node.right;
        return os;
    }


};

#endif //RATTLE_BINNODE_HPP
