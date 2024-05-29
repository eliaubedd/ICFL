#ifndef ICFL_MYTREE_HPP
#define ICFL_MYTREE_HPP

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <iostream>
#include <utility>
#include <ostream>

/**
 * @class Node
 * @brief Rappresenta un nodo in una struttura ad albero.
 *
 * La classe Node rappresenta un nodo all'interno di una struttura ad albero.
 * Ogni nodo contiene informazioni sul nodo stesso, come il genitore, i figli, gli indici, la lista g-list,
 * l'insertion target e un puntatore a un oggetto BitVector.
 */
class Node{

private:
    Node *_parent; ///< Puntatore al nodo genitore.
    std::vector<Node*> _children; ///< Vettore di puntatori ai nodi figli.
    std::pair<unsigned int, unsigned int> _indexes; ///< Coppia di indici che rappresenta l'intervallo associato al suffisso.
    std::vector<int> _g_list; ///< g-list associata al nodo.
    unsigned int _insertion_target; ///< Insertion target associato al nodo.
    pasta::BitVector *_bv; ///< Puntatore a un oggetto BitVector associato al nodo.

public:
    /**
     * @brief Costruttore di default.
     */
    Node() : _parent(nullptr), _children(), _indexes(), _g_list(), _insertion_target(), _bv(nullptr) {}

    /**
     * @brief Costruttore base.
     * @param parent Puntatore al nodo genitore.
     * @param children Vettore di puntatori ai nodi figli.
     * @param indexes Coppia di indici che rappresenta l'intervallo associato al nodo.
     * @param g_list Lista G associata al nodo.
     * @param insertion_target Punto di inserimento associato al nodo.
     * @param bv Puntatore a un oggetto BitVector associato al nodo.
     */
    Node(Node* parent, std::vector<Node*> children, std::pair<unsigned int, unsigned int> indexes,
         std::vector<int> g_list, unsigned int insertion_target, pasta::BitVector *bv)
            : _parent(parent), _children(std::move(children)), _indexes(std::move(indexes)), _g_list(std::move(g_list)), _insertion_target(insertion_target) {
        _bv = bv;
    }

    /**
     * @brief Operatore di assegnamento.
     * @param other Nodo da cui copiare.
     * @return Nodo modificato.
     */
    Node& operator=(const Node& other) {
        if (this != &other) {
            _parent = other._parent;
            _children = other._children;
            _indexes = other._indexes;
            _g_list = other._g_list;
            _insertion_target = other._insertion_target;
            _bv = other._bv;
        }
        return *this;
    }

    /**
     * @brief Operatore di stream di output.
     * @param os Stream di output.
     * @param node Nodo da stampare.
     * @return Stream di output modificato.
     */
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
        os << "Insertion target: " << node._insertion_target << std::endl;
        os << "BitVector: "; print_bv(*(node._bv));
        return os;
    }
};

class Tree{

};

#endif //ICFL_MYTREE_HPP
