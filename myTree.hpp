#ifndef ICFL_MYTREE_HPP
#define ICFL_MYTREE_HPP

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>"
#include <iostream>
#include <utility>
#include <ostream>

class Node{

private:
    Node *_parent;
    std::vector<Node*> _children;
    //-> attributes
    std::pair<unsigned int, unsigned int> _indexes;
    std::vector<int> _g_list;
    pasta::BitVector *_bv;

public:
    //Costruttore di default
    Node() : _parent(nullptr), _children(), _indexes(), _g_list(), _bv(nullptr) {}

    //Costruttore base
    Node(Node* parent, std::vector<Node*> children, std::pair<unsigned int, unsigned int> indexes,
         std::vector<int> g_list, pasta::BitVector *bv)
            : _parent(parent), _children(std::move(children)), _indexes(std::move(indexes)), _g_list(std::move(g_list)) {
        _bv = bv;
    }

    //Costruttore copia
    Node(const Node& other)
            : _parent(other._parent), _children(other._children), _indexes(other._indexes),
              _g_list(other._g_list)
    {
        _bv = other._bv;
    }

    // Operatore di assegnamento
    Node& operator=(const Node& other) {
        if (this != &other) {
            _parent = other._parent;
            _children = other._children;
            _indexes = other._indexes;
            _g_list = other._g_list;
            _bv = other._bv;
        }
        return *this;
    }

    // Distruttore
    ~Node() {
        delete _bv;
    }


    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << "Parent: " << node._parent << std::endl;
        os << "Children: ";
        for (const auto& child : node._children) {
            os << child << " ";
        }
        os << std::endl;
        os << "Indexes: (" << node._indexes.first << ", " << node._indexes.second << ")" << std::endl;
        os << "G List: ";
        for (const auto& index : node._g_list) {
            os << index << " ";
        }
        os << std::endl;
        os << "BitVector: "; print_bv(*(node._bv));
        return os;
    }
};

class Tree{

};





#endif //ICFL_MYTREE_HPP
