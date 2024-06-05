#ifndef ICFL_TREE_HPP
#define ICFL_TREE_HPP

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <string>
#include <vector>
#include "node.hpp"

class Tree {

private:
    Node* _root;
    std::list<std::string> _icfl;

public:
    Tree(const std::list<std::string> &icfl) : _icfl(icfl){
        std::string text;
        for (const std::string& factor : icfl) {
            text += factor;
        }
        _root = new Node(text, icfl.size());
    }

    ~Tree() {
        delete _root;
    }

    const std::list<std::string>& get_icfl() const {
        return _icfl;
    }

    void set_text(const std::list<std::string>& icfl) {
        if(!_root->get_text().empty()){
            std::cout << "ERROR: text already setted";
            return;
        }
        _icfl = icfl;
        std::string text;
        for (const std::string& factor : icfl) {
            text += factor;
        }
        if (_root) {
            delete _root;
        }
        _root = new Node();
        _root->set_text(text);
    }

    Node* get_root() const {
        return _root;
    }
};

#endif // ICFL_TREE_HPP
