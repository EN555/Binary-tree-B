//
// Created by eviat on 5/21/2021.
//

#ifndef BINARY_TREE_A_BINARYTREE_HPP
#define BINARY_TREE_A_BINARYTREE_HPP

#include "inorder_traversal.hpp"
#include "preorder_traversal.hpp"
#include "postorder_traversal.hpp"
#include "Node.hpp"
#include <set>
#include <exception>


namespace ariel {
    template<typename T>
    class BinaryTree {

    public:
        Node<T> *root;     //root of the tree
        BinaryTree(){
            root = nullptr;
        }
        ~BinaryTree(){  //pre order travers and delete all
            releaseNodes(this->root);
        }

        BinaryTree<T>& operator=(const BinaryTree<T>& b){
            if(this == &b){
                return *this;
            }

            releaseNodes(this->root);
            cop(b);
            return  *this;
        }
        //copy constructor
        BinaryTree<T>(const BinaryTree<T>& other){
                cop(other);

        }

        void releaseNodes(Node<T>* current_node) {
            if (current_node == nullptr) { return; }
            releaseNodes(current_node->left);
            releaseNodes(current_node->right);
            delete current_node;
        }

        BinaryTree& add_root(T value){
            if(!root) {     //if the root already exist
                root = new Node<T>(value, nullptr, nullptr);
                return *this;
            }
            root ->val = value;     //otherwise change the value of the node
            return *this;
        }

        BinaryTree &add_left(T father, T val){
        auto iter = begin_postorder();
        auto end = end_postorder();
            while (iter != end && !(*iter == father)) { ++iter; }
            if (iter == end) { throw std::invalid_argument(""); }
            if (!((*(iter.it))->left)) { (*(iter.it))->left = new Node<T>(val); }
            else { (*(iter.it))->left->val = val; } // change
            return *this;
        }

        BinaryTree &add_right(T father, T val){
            auto iter = begin_postorder();
            auto end = end_postorder();
            while (iter != end && !(*iter == father)) { ++iter; }
            if (iter == end) { throw std::invalid_argument(""); }
            if (!((*(iter.it))->right)) { (*(iter.it))->right = new Node<T>(val); }
            else { (*(iter.it))->right->val = val; }
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> tree){
            return os;
        }


        void cop(const BinaryTree &other){

            if (other.root)
            {
                root = new Node<T>{other.root->val};
                copy(root, other.root);
            }

        }

        void copy(Node<T> *dst, Node<T> *src)
        {
            if (src->right)
            {
                dst->right = new Node<T>{src->right->val};
                copy(dst->right, src->right);
            }

            if (src->left)
            {
                dst->left = new Node<T>{src->left->val};
                copy(dst->left, src->left);
            }

        }

        BinaryTree(BinaryTree &&other) noexcept
        {
            root = other.root;
            remove_nodes();
            root = other.root;
            other.root = nullptr;
        }

        BinaryTree<T>& operator=(BinaryTree<T> &&other) noexcept
        {
            remove_nodes();
            root = other.root;
            other.root = nullptr;
            return *this;
        }



        void remove_nodes(){
                releaseNodes(this->root);
        }
        preorder_traversal<T> begin_preorder(){
            return preorder_traversal<T>{root};
        }

        postorder_traversal<T> begin_postorder(){
            return postorder_traversal<T>{root};
        }

        inorder_traversal<T> begin_inorder(){
            return inorder_traversal<T>{root};
        }

        preorder_traversal<T> end_preorder(){
            return preorder_traversal<T>{root, true};
        }

        postorder_traversal<T> end_postorder(){
            return postorder_traversal<T>{root, true};
        }

        inorder_traversal<T> end_inorder(){
            return inorder_traversal<T>{root, true};
        }

        inorder_traversal<T> begin(){
            return inorder_traversal<T>{root};
        }

        inorder_traversal<T> end(){
            return inorder_traversal<T>{root, true};
        }

    };


};


















#endif //BINARY_TREE_A_BINARYTREE_HPP
