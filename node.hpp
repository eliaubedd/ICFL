#ifndef ICFL_NODE_HPP
#define ICFL_NODE_HPP

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
    Node* _parent; ///< Puntatore al nodo genitore.
    Node* _root;
    std::string _text;
    std::vector<Node*> _children; ///< Vettore di puntatori ai nodi figli.
    std::pair<unsigned int, unsigned int> _indexes; ///< Coppia di indici che rappresenta l'intervallo associato al suffisso.
    std::vector<int> _g_list; ///< g-list associata al nodo.
    unsigned int _insertion_target; ///< Insertion target associato al nodo.
    pasta::BitVector* _bv; ///< Puntatore a un oggetto BitVector associato al nodo.


public:



    /**
    * @brief Costruttore di default.
    */
    Node() : _root(this), _parent(nullptr), _text(), _children(), _indexes(0, 0), _g_list(), _insertion_target(0), _bv(nullptr) {
        _bv = new pasta::BitVector(1, 0);
    }

    Node(const std::string& text, size_t bv_size)
            : _root(this), _parent(nullptr), _text(text), _children(), _indexes(0, 0), _g_list(), _insertion_target(0) {
        _bv = new pasta::BitVector(bv_size, 0);
    }


    /**
     * @brief Costruttore base.
     * @param parent Puntatore al nodo genitore.
     * @param children Vettore di puntatori ai nodi figli.
     * @param indexes Coppia di indici che rappresenta l'intervallo associato al nodo.
     * @param g_list Lista G associata al nodo.
     * @param insertion_target Punto di inserimento associato al nodo.
     * @param bv Puntatore a un oggetto BitVector associato al nodo.
     */
    Node(Node* root, Node* parent, std::vector<Node*> children, std::pair<unsigned int, unsigned int> indexes,
         std::vector<int> g_list, unsigned int insertion_target, pasta::BitVector *bv):

         _root(root), _parent(parent), _children(std::move(children)), _indexes(std::move(indexes)),
         _g_list(std::move(g_list)), _insertion_target(insertion_target), _text(root->get_text()){

            if (bv != nullptr) {
                _bv = new pasta::BitVector(bv->size(), 0);
                for (unsigned int i = 0; i < bv->size(); ++i) {
                    (*_bv)[i] = (*bv)[i] ? 1 : 0; // = is assignment operator for bv, not ==
                }
            } else {
                _bv = nullptr;
            }

         }

    /**
    * @brief Costruttore di copia.
    * @param other Nodo da cui copiare.
    */
    Node(const Node& other) : _root(other._root), _parent(other._parent), _children(other._children), _indexes(other._indexes),
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

    /**
    * @brief Operatore di assegnamento.
    * @param other Nodo da cui copiare.
    * @return Nodo modificato.
    */
    Node& operator=(const Node& other) {
        if (this != &other) {
            _root = other._root;
            _parent = other._parent;
            _children = other._children;
            _indexes = other._indexes;
            _g_list = other._g_list;
            _insertion_target = other._insertion_target;
            _text = other._text;
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

    ~Node() {
        delete _bv;
    }

    /**
    * @brief Restituisce il puntatore al nodo genitore.
    * @return Puntatore al nodo genitore.
    */
    Node* get_parent() const {
        return _parent;
    }

    std::string get_suffix() const {
        if (_indexes == std::make_pair(0, 0)){
            return "";
        }
        int second = _indexes.second;
        if (second > _text.size()) {
            throw std::out_of_range("Index out of range in get_suffix()");
        }
        return _text.substr(_indexes.first, _indexes.second - _indexes.first);
    }

    std::string get_text() const{
        return _text;
    }

    std::vector<Node*> get_children() const {
        return _children;
    }

    void set_text(const std::string& text) {
        _text = text;
        for (auto child : _children) {
            if (child) {
                child->set_text(text);
            }
        }
    }

    void set_bv(pasta::BitVector &bv){
        _bv = &bv;
    }

    void set_parent(Node *node){
        _parent = node;
    }

    /**
    * @brief Imposta i figli del nodo.
    * @param children Vettore di puntatori ai nodi figli.
    */
    void set_children(std::vector<Node*> children) {
        _children = std::move(children);
    }

    /**
    * @brief Funzione di confronto per ordinare i figli in ordine lessicografico.
    * @param a Puntatore al primo nodo.
    * @param b Puntatore al secondo nodo.
    * @return True se il nodo a deve precedere il nodo b.
    */
    static bool compare_nodes (Node *a, Node *b){
        std::string suffix_a = a->get_suffix();
        std::string suffix_b = b->get_suffix();
        return suffix_a < suffix_b;
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
    pasta::BitVector* get_bv_pointer() const{
        return _bv;
    }

    void print_bv() {
        for (auto &it: *_bv) {
            std::cout << (it ? '1' : '0');
        }
        std::cout << std::endl;
    }

    void print_children(){
        for(auto child : _children){
            std::cout << *child << " , ";
        }
        std::cout << std::endl;
    }

    void print_data() {
        std::cout << "-----NODE " << get_suffix() << " -----" << std::endl;
        if (_indexes == std::make_pair(0, 0)) {
            std::cout << "this node is the ROOT" << std::endl;
            return;
        }
        std::cout << "Node: " << get_suffix() << std::endl;
        if (_parent) {
            std::cout << "Parent: " << *_parent << std::endl;
        } else {
            std::cout << "Parent: None" << std::endl;
        }
        std::cout << "Children: ";
        for (const auto& child : _children) {
            std::cout << *child << " ";
        }
        std::cout << std::endl;
        std::cout << "Indexes: (" << _indexes.first << ", " << _indexes.second << ")" << std::endl;
        std::cout << "G List: ";
        for (const auto& index : _g_list) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
        std::cout << "Insertion target: " << _insertion_target << std::endl;
        if (_bv) {
            std::cout << "BitVector: "; print_bv();
        } else {
            std::cout << "BitVector: None" << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        if(node.get_suffix() != ""){
            os << node.get_suffix();
        }
        else{
            os << "ROOT";
        }
        return os;
    }

};

#endif //ICFL_NODE_HPP
