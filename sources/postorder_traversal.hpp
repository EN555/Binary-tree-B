//
// Created by eviat on 5/23/2021.
//

#ifndef BINARY_TREE_A_POSTORDER_TRAVERSAL_HPP
#define BINARY_TREE_A_POSTORDER_TRAVERSAL_HPP
#include "Node.hpp"
#include <vector>
#include <exception>

namespace ariel {
    template<typename T>
    class postorder_traversal {
    private:
        std::vector<Node<T> *> pre_nodes;
    public:
        typename std::vector<Node<T>*>::iterator it;

        postorder_traversal(Node<T> *curr, bool is_end= false){
            traverse_postorder(curr); //insert all the nodes to the vector
            pre_nodes.push_back(nullptr);
            if(!is_end){
                it = pre_nodes.begin();
            }
            else{
                it = --pre_nodes.end();
            }
        }
        postorder_traversal(const  postorder_traversal&& other) noexcept: pre_nodes(other.pre_nodes){
            this -> it = this->pre_nodes.begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++){
                ++((this->it));
            }
        }

        postorder_traversal& operator=(const  postorder_traversal && other) noexcept{
            this->pre_nodes = other.pre_nodes;
            this -> it = (this->pre_nodes).begin();
            int counter = other.it - other.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++) {
                ++((this->it));
            }
            return  *this;
        }

        //destructor
        ~postorder_traversal() = default;

        postorder_traversal(const  postorder_traversal& other) :pre_nodes(other.pre_nodes) {

                this->it = (this->pre_nodes).begin();
                int counter = other.it - other.pre_nodes.begin();
                for (int i = 0; i < counter; i++) {
                    ++((this->it));
                }
        }

        postorder_traversal<T>& operator=(const  postorder_traversal<T>& b){
            if(this == &b){return *this;}
            this->pre_nodes = b.pre_nodes;
            this -> it = (this->pre_nodes).begin();
            int counter = b.it - b.pre_nodes.begin();
            for(int i= 0 ; i < counter; i++) {
                ++((this->it));
            }
            return *this;
        }

        void traverse_postorder(Node<T> *node) {
            if (node == nullptr) {
                return;
            }
            traverse_postorder(node->left);
            traverse_postorder(node->right);
            pre_nodes.emplace_back(node);
        }

        T &operator*() const {
            //return *pointer_to_current_node;
            return (*it) ->val;
        }

        // ++i;
        postorder_traversal &operator++() {
            //++pointer_to_current_node;
            ++it;
            return *this;
        }

        // i++;
        // Usually iterators are passed by value and not by const& as they are small.
        const postorder_traversal operator++(int) {
            postorder_traversal<T> tmp = *this;
            ++it;
            return tmp;
        }

        bool operator==(const postorder_traversal& rhs) const {
            return *(this->it) == *(rhs.it);
        }

        bool operator!=(const postorder_traversal& rhs) const {
            return *(this->it) != *(rhs.it);
        }

        T* operator->() const {
            return &((*it)-> val);
        }
    };
};
#endif //BINARY_TREE_A_POSTORDER_TRAVERSAL_HPP
