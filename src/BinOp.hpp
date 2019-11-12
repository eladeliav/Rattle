//
// Created by elade on 11/12/2019.
//

#ifndef RATTLE_BINOP_HPP
#define RATTLE_BINOP_HPP

#include <iostream>
#include "Token.hpp"


class BinOp {
public:
    BinOp()
    = default;

    Token key;     ///< The key of the BinOp
    BinOp* left;    ///< The left child of the BinOp
    BinOp* right;   ///< The right child of the BinOp

    virtual ~BinOp()
    {
        std::cout << "destructor of binop" << std::endl;
    }

    /**
     * @brief Constructor of a binary search tree BinOp
     */
    BinOp(const Token key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

#endif //RATTLE_BINOP_HPP
