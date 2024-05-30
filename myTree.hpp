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

    static const std::string* _T; ///< Puntatore alla stringa globale T.

public:

    /**
    * @brief Imposta la stringa globale T.
    * @param T Puntatore alla stringa T.
    */
    static void set_global_text(const std::string* T) {
        _T = T;
    }

    /**
    * @brief Funzione di confronto per ordinare i figli in ordine lessicografico.
    * @param a Puntatore al primo nodo.
    * @param b Puntatore al secondo nodo.
    * @return True se il nodo a deve precedere il nodo b.
    */
    static bool compare_nodes (Node *a, Node *b){
        std::string suffix_a = _T->substr(a->_indexes.first, a->_indexes.second - a->_indexes.first);
        std::string suffix_b = _T->substr(b->_indexes.first, b->_indexes.second - b->_indexes.first);
        return suffix_a < suffix_b;
    }

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
         std::vector<int> g_list, unsigned int insertion_target, pasta::BitVector *bv):
         _parent(parent), _children(std::move(children)), _indexes(std::move(indexes)),
         _g_list(std::move(g_list)), _insertion_target(insertion_target)
         {
            _bv = new pasta::BitVector(bv->size(), 0);
            for (unsigned int i = 0; i < bv->size(); ++i) {
                (*_bv)[i] = (*bv)[i] ? 1 : 0; // = is comparison operator for bv, not ==
            }
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
            delete _bv;
            if (other._bv) {
                _bv = new pasta::BitVector(other._bv->size(), false);
                for (size_t i = 0; i < other._bv->size(); ++i) {
                    (*_bv)[i] = (*other._bv)[i] ? 1 : 0;
                }
            } else {
                _bv = nullptr;
            }
        }
        return *this;
    }

    /**
     * @brief Costruttore di copia.
     * @param other Nodo da cui copiare.
     */
    Node(const Node& other) : _parent(other._parent), _children(other._children), _indexes(other._indexes),
                              _g_list(other._g_list), _insertion_target(other._insertion_target) {
        if (other._bv) {
            _bv = new pasta::BitVector(other._bv->size(), false);
            for (size_t i = 0; i < other._bv->size(); ++i) {
                (*_bv)[i] = (*other._bv)[i] ? 1 : 0;
            }
        } else {
            _bv = nullptr;
        }
    }

    std::string get_suffix(){
        return _T->substr(_indexes.first, _indexes.second - _indexes.first);
    }

    /**
    * @brief Restituisce il puntatore al nodo genitore.
    * @return Puntatore al nodo genitore.
    */
    Node* get_parent() const {
        return _parent;
    }

    /**
    * @brief Imposta i figli del nodo.
    * @param children Vettore di puntatori ai nodi figli.
    */
    void set_children(std::vector<Node*> children) {
        _children = std::move(children);
    }

    /**
     * @brief Aggiunge un figlio mantenendo l'ordine lessicografico.
     * @param node Puntatore al nodo figlio da aggiungere.
     */
    void add_child(Node* node) {
        _children.push_back(node);
        std::sort(_children.begin(), _children.end(), compare_nodes);
    }

    /**
    * @brief Restituisce il suffisso associato al nodo.
    * @return Il suffisso associato al nodo.
    */
    pasta::BitVector* get_bv_pointer(){
        return _bv;
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
