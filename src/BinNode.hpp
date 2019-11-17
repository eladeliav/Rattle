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


    explicit BinNode(BinNode *pNode)
    {
        key = Token(pNode->key);
        if (pNode->left)
            left = new BinNode(pNode->left);  // recursively call copy constructor
        if (pNode->right)
            right = new BinNode(pNode->right);  // recursively call copy constructor
    }

    Token key;     ///< The key of the BinOp
    BinNode *left = nullptr;    ///< The left child of the BinOp
    BinNode *right = nullptr;   ///< The right child of the BinOp

    virtual ~BinNode()
    {
        std::cout << "destructor of binop" << std::endl;
        delete left;
        delete right;
    }

    /**
     * @brief Constructor of a binary search tree BinOp
     */
    explicit BinNode(const Token& key)
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
