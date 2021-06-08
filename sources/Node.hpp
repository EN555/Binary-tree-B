//
// Created by eviat on 5/23/2021.
//

#ifndef BINARY_TREE_A_NODE_HPP
#define BINARY_TREE_A_NODE_HPP
#include <iostream>


namespace ariel {
    template<typename T>
    struct Node {
        T val;
        Node *left;
        Node *right;

        //ls- left side rs- right side
        Node(T value= T{}, Node *ls = nullptr, Node *rs = nullptr):val(value),left(ls),right(rs){}

    };
};
#endif //BINARY_TREE_A_NODE_HPP
