#ifndef ICFL_TREE_HPP
#define ICFL_TREE_HPP

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <iostream>
#include <utility>
#include <ostream>
#include "node.hpp"

class Tree{

private:
    Node* _root;
    std::string _text;

public:
    Tree() : _root(){};

    Tree(const std::string &text, Node& root) : _text(text), _root(&root){};

    const std::string& get_text() const {
        return _text;
    }

    void set_root(Node* root) {
        _root = root;
        if (root) {
            root->set_text(_text);
        }
    }

    Node* get_root() const{
        return _root;
    }


};

#endif //ICFL_TREE_HPP
