//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_BINNODE_HPP
#define RATTLE_BINNODE_HPP

#include <iostream>
#include "Token.hpp"


class BinNode {
public:
    BinNode()
    = default;

    Token key;     ///< The key of the BinOp
    BinNode* left;    ///< The left child of the BinOp
    BinNode* right;   ///< The right child of the BinOp

    virtual ~BinNode()
    {
        std::cout << "destructor of binop" << std::endl;
    }

    /**
     * @brief Constructor of a binary search tree BinOp
     */
    BinNode(const Token key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

#endif //RATTLE_BINNODE_HPP
