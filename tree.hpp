#ifndef ICFL_TREE_HPP
#define ICFL_TREE_HPP

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <string>
#include <vector>
#include "node.hpp"

/**
 * @class Tree
 * @brief La classe Tree rappresenta una struttura ad albero con nodi di tipo Node.
 *
 * Questa classe gestisce un albero con radice _root e mantiene una lista di stringhe
 * chiamata _icfl (Inverse Lyndon Factorization)
 */
class Tree {

private:
    Node* _root;  ///< Puntatore al nodo radice dell'albero.
    std::list<std::string> _icfl;  ///< Lista di stringhe rappresentante l'ICFL.

public:
    /**
     * @brief Costruttore della classe Tree.
     *
     * Costruisce un oggetto Tree con la lista ICFL fornita. Inizializza il nodo _root
     * con il testo concatenato dell'ICFL e la dimensione della lista ICFL.
     *
     * @param icfl Lista di stringhe che rappresentano l'ICFL.
     */
    Tree(const std::list<std::string> &icfl) : _icfl(icfl) {
        std::string text;
        for (const std::string& factor : icfl) {
            text += factor;
        }
        _root = new Node(text, icfl.size());
    }

    /**
     * @brief Distruttore della classe Tree.
     *
     * Distrugge l'oggetto Tree e dealloca la memoria del nodo radice.
     */
    ~Tree() {
        delete _root;
    }

    /**
     * @brief Restituisce la lista ICFL.
     *
     * @return Una referenza costante alla lista di stringhe ICFL.
     */
    const std::list<std::string>& get_icfl() const {
        return _icfl;
    }

    /**
     * @brief Imposta il testo del nodo radice con il testo concatenato dell'ICFL fornita.
     *
     * Se il testo del nodo radice è già stato impostato, visualizza un messaggio di errore.
     *
     * @param icfl Lista di stringhe che rappresentano l'ICFL.
     */
    void set_text(const std::list<std::string>& icfl) {
        if(!_root->get_text().empty()) {
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

    /**
     * @brief Restituisce il puntatore al nodo radice.
     *
     * @return Un puntatore costante al nodo radice.
     */
    Node* get_root() const {
        return _root;
    }
};

#endif // ICFL_TREE_HPP
