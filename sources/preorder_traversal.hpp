//
// Created by eviat on 5/23/2021.
//

#ifndef BINARY_TREE_A_PREORDER_TRAVERSAL_HPP
#define BINARY_TREE_A_PREORDER_TRAVERSAL_HPP
#include "Node.hpp"
#include <vector>
#include <exception>


namespace ariel {
    template<typename T>
    class preorder_traversal {
    private:
        std::vector<Node<T>*> pre_nodes;
    public:
        typename std::vector<Node<T>*>::iterator it;

        preorder_traversal(Node<T> *curr, bool is_end= false){
            traverse_preorder(curr); //insert all the nodes to the vector
            pre_nodes.push_back(nullptr);
            if(!is_end) {
                it = pre_nodes.begin();}
            else {it = --pre_nodes.end();}
        }

        void traverse_preorder(Node<T> *node){
            if(node == nullptr){
                return;
            }
            pre_nodes.emplace_back(node);
            traverse_preorder(node ->left);
            traverse_preorder(node->right);
        }

        preorder_traversal(const  preorder_traversal&& other) noexcept: pre_nodes(other.pre_nodes){
            this -> it = this->pre_nodes.begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++){
                ++((this->it));
            }
        }

        preorder_traversal& operator=(const  preorder_traversal && other) noexcept{
            this->pre_nodes = other.pre_nodes;
            this -> it = (this->pre_nodes).begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++) {
                ++((this->it));
            }
            return  *this;
        }

        //destructor
        ~preorder_traversal() = default;

        preorder_traversal(const  preorder_traversal& other) :pre_nodes(other.pre_nodes) {

                this->it = (this->pre_nodes).begin();
                int counter = other.it - other.pre_nodes.begin();
                for (int i = 0; i < counter; i++) {
                    ++((this->it));
                }
        }

        preorder_traversal<T>& operator=(const  preorder_traversal<T>& other){
            if(this == &other){return *this;}
            this->pre_nodes = other.pre_nodes;
            this -> it = (this->pre_nodes).begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++) {
                ++((this->it));
            }
            return *this;
        }

 T &operator*() const {
            //return *pointer_to_current_node;
            return (*it)->val;
        }

        // ++i;
        preorder_traversal &operator++() {
            //++pointer_to_current_node;
            ++it;
            return *this;
        }

        // i++;
        // Usually iterators are passed by value and not by const& as they are small.
        const preorder_traversal operator++(int) {
            preorder_traversal<T> tmp = *this;
            ++it;
            return tmp;
        }

        bool operator==(const preorder_traversal& rhs) const {
            return *(this->it) == *(rhs.it);
        }

        bool operator!=(const preorder_traversal& rhs) const {
            return pre_nodes.empty() != rhs.pre_nodes.empty() || *(this->it) != *(rhs.it);
        }

        T* operator->() const {
            return &((*it)-> val);
        }
    };
};
#endif //BINARY_TREE_A_PREORDER_TRAVERSAL_HPP
