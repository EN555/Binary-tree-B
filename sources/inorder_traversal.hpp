//
// Created by eviat on 5/23/2021.
//

#ifndef BINARY_TREE_A_INORDER_TRAVERSAL_HPP
#define BINARY_TREE_A_INORDER_TRAVERSAL_HPP

#include "Node.hpp"
#include <vector>
#include <exception>

namespace ariel {
    template<typename T>
    class inorder_traversal {
    private:
        std::vector<Node<T> *> pre_nodes;

    public:
        typename std::vector<Node<T>*>::iterator it;

        inorder_traversal(Node<T> *curr, bool is_end = false){
            traverse_inorder(curr); //insert all the nodes to the vector
            pre_nodes.push_back(nullptr);
            if(!is_end){
                this->it = pre_nodes.begin();
            }
            else{
                this-> it= --pre_nodes.end();
            }
        }

        void traverse_inorder(Node<T> *node) {
            if (node == nullptr) {
                return;
            }
            traverse_inorder(node->left);
            pre_nodes.emplace_back(node);
            traverse_inorder(node->right);
        }


        T &operator*() const {
            //return *pointer_to_current_node;
            return (*(this->it))->val;
        }

        // ++i;
        inorder_traversal &operator++() {
            //++pointer_to_current_node;
            ++(this->it);
            return *this;
        }

        inorder_traversal(const inorder_traversal&& other) noexcept: pre_nodes(other.pre_nodes){
            this -> it = this->pre_nodes.begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++){
                ++((this->it));
            }
        }

        inorder_traversal<T>& operator=(const inorder_traversal && other) noexcept{
            this->pre_nodes = other.pre_nodes;
            this -> it = (this->pre_nodes).begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++) {
                ++((this->it));
            }
            return  *this;
        }

        inorder_traversal(const inorder_traversal& other) :pre_nodes(other.pre_nodes) {
                this->it = (this->pre_nodes).begin();
                int counter = other.it - other.pre_nodes.begin();
                for (int i = 0; i < counter; i++) {
                    ++((this->it));
                }

        }

        inorder_traversal<T>& operator=(const inorder_traversal<T> & other){
            if(this == &other){return *this;}
            this->pre_nodes = other.pre_nodes;
            this -> it = (this->pre_nodes).begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++) {
                ++((this->it));
            }
            return *this;
        }

        // i++;
        // Usually iterators are passed by value and not by const& as they are small.
        const inorder_traversal operator++(int) {
            inorder_traversal<T> tmp = *this;
            ++(this->it);
            return tmp;
        }

        bool operator==(const inorder_traversal &rhs) const {
            return *(this->it) == *(rhs.it);
        }

        bool operator!=(const inorder_traversal &rhs) const {
            return *(this->it) != *(rhs.it);
        }

        T* operator->() const {
            return &((*(this->it))-> val);
        }
    };
};
#endif //BINARY_TREE_A_INORDER_TRAVERSAL_HPP
