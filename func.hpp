/**
 * @file funch.cpp
 * @brief Contiene le funzioni di supporto per BitVector e List, .
 */

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <tree.hh>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "tree.hpp"
#include "node.hpp"

/**
 * @brief Costruisce e restituisce una lista di stringhe da un file di testo.
 *
 * Questa funzione legge da un file di testo il numero di nodi seguito da una serie di stringhe e costruisce una
 * lista di stringhe con i contenuti letti dal file.
 * Se il file non può essere aperto o se si verificano errori durante la lettura, viene lanciata un'eccezione
 * std::runtime_error.
 *
 * @param filename Il nome del file di testo da leggere.
 * @return Una lista di stringhe contenente i dati letti dal file.
 * @throw std::runtime_error Se si verificano errori durante l'apertura del file o durante la lettura dei dati.
 */
std::list<std::string> build_input_ICFL(const std::string& filename) {
    std::ifstream file(filename);
    std::list<std::string> icfl_t;

    if(file.is_open()){
        int num_nodes;
        if (!(file >> num_nodes)) {
            throw std::runtime_error("Errore reading file: " + filename);
        }
        file.ignore(); // Ignora il carattere di nuova riga dopo l'intero
        for (int i = 0; i < num_nodes; ++i) {
            std::string node_data;
            if (!std::getline(file, node_data)) {
                throw std::runtime_error("Error.");
            }
            icfl_t.push_back(node_data);
        }
        file.close();
    }
    else{
        throw std::runtime_error("Cannot open file: " + filename);
    }
    return icfl_t;
}

/**
 * @brief Costruisce una stringa concatenando tutti gli elementi di una lista di stringhe.
 *
 * Questa funzione scorre attraverso una lista di stringhe, concatenando ciascun elemento in un'unica stringa finale.
 *
 * @param icfl_t La lista di stringhe da concatenare.
 * @return Una stringa che contiene tutti gli elementi della lista concatenati.
 */
std::string build_text_from_ICFL(std::list<std::string> &icfl_t){
    auto it = icfl_t.begin();
    std::string text = "";
    while(it != icfl_t.end()){
        text = text + *it;
        ++it;
    }
    return text;
}

/**
 * @brief Costruisce e restituisce una lista di stringhe di esempio.
 *
 * Costruisce una lista di stringhe di esempio e la restituisce.
 * ICFL(T) = < aaa baa caabca dcaabca >
 *
 * @return Lista di stringhe.
 */
std::list<std::string> build_ICFL(){
    std::list<std::string> icfl_text;
    icfl_text.push_back("aaa");
    icfl_text.push_back("baa");
    icfl_text.push_back("caabca");
    icfl_text.push_back("dcaabca");
    return icfl_text;
}

/**
 * @brief Costruisce e restituisce una [x]_g-list di esempio.
 *
 * Costruisce una lista di interi di esempio e la restituisce.
 * [x]_g-list =  < 19 3 6 12 >
 *
 * @return Lista di interi.
 */
std::list<int> build_xgList(){
    std::list<int> xglist;
    xglist.push_back(19);
    xglist.push_back(3);
    xglist.push_back(6);
    xglist.push_back(12);
    return xglist;
}

/**
 * @brief Costruisce e restituisce una [z]_g-list di esempio.
 *
 * Costruisce una lista di interi di esempio e la restituisce.
 * [z]_g-list =  < 16 9 >
 *
 * @return Lista di interi.
 */
std::list<int> build_zgList(){
    std::list<int> zglist;
    zglist.push_back(16);
    zglist.push_back(9);
    return zglist;
}

/**
 * @brief Stampa gli elementi di una lista generica.
 *
 * Stampa gli elementi contenuti in una lista generica.
 *
 * @tparam T Tipo degli elementi contenuti nella lista.
 * @param list Lista da stampare.
 */
template <typename T>
void print_list(std::list<T> &list){
    std::cout << " [ ";
    for (const T& x : list) {
        std::cout << x << " ";
    }
    std::cout << "] " << std::endl;
}

/**
 * @brief Stampa i bit presenti in un oggetto BitVector.
 *
 * Stampa i bit presenti in un oggetto BitVector.
 *
 * @param bv Oggetto BitVector da stampare.
 */
void print_bv(const pasta::BitVector &bv) {
    std::cout <<"[ ";
    for (auto &it: bv) {
        std::cout << (it ? '1' : '0') << " ";
    }
    std::cout << "]" << std::flush;
}

/**
 * @brief Stampa il contenuto di un vettore g_list.
 * @param g_list Vettore di interi da stampare.
 *
 * Questa funzione prende un vettore di interi e stampa il suo contenuto
 * in formato [ elemento1 elemento2 ... elementoN ].
 */
void print_g_list_vector(const std::vector<int>& g_list) {
    std::cout << "[";
    for (size_t i = 0; i < g_list.size(); ++i) {
        std::cout << g_list[i];
        if (i != g_list.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Stampa il contenuto di una mappa con chiave stringa e valore BitVector.
 * @param map Mappa con chiavi di tipo std::string e valori di tipo pasta::BitVector.
 *
 * Questa funzione itera attraverso una mappa e per ogni coppia chiave-valore,
 * stampa la chiave e chiama `print_bv` per stampare il valore (un oggetto BitVector).
 */
void print_bit_map(const std::unordered_map<std::string, pasta::BitVector>& map) {
    for (const auto& pair : map) {
        std::cout << "Chiave: " << pair.first << ", Valore: ";
        print_bv(pair.second);  // Chiama `print_bv` per stampare il valore
        std::cout << std::endl;
    }
}

/**
 * @brief Stampa il contenuto di una mappa con chiave e valore stringa.
 * @param map Mappa con chiavi di tipo std::string e valori di tipo std::string.
 *
 * Questa funzione itera attraverso una mappa e per ogni coppia chiave-valore,
 * stampa la chiave (rappresentante un nodo) e il valore associato (rappresentante il genitore del nodo).
 */
void print_node_map(const std::unordered_map<std::string, std::string>& map) {
    for (const auto& pair : map) {
        std::cout << "NODO: " << pair.first << ", GENITORE: " << pair.second << std::endl;
    }
}

/**
 * @brief Trova l'elemento all'indice specificato in una lista.
 *
 * Questa funzione cerca l'elemento all'indice specificato nella lista data e restituisce un iteratore
 * alla sua posizione se trovato. Se l'indice specificato è fuori dall'intervallo della lista,
 * viene lanciata un'eccezione std::out_of_range.
 *
 * @tparam T Il tipo degli elementi memorizzati nella lista.
 * @param list La lista in cui effettuare la ricerca.
 * @param i L'indice dell'elemento da trovare.
 * @return Un iteratore alla posizione dell'elemento all'indice specificato se trovato.
 * @throw std::out_of_range se l'indice specificato è fuori dall'intervallo della lista.
 */
template <typename T>
typename std::list<T>::iterator find_node(std::list<T> &list, unsigned int i){
    unsigned int count = 0;
    auto it = list.begin();
    while (it != list.end()) {
        if (count == i){
            return it;
        }
        ++it;
        ++count;
    }
    throw std::out_of_range("Indice fuori dalla lista");
}

/**
 * @brief Calcola e restituisce il punto di inserimento "insertion target" in base ai parametri forniti.
 *
 * Calcola e restituisce il punto di inserimento "insertion target" in base ai parametri forniti.
 *
 * @param b_x BitVector associato al suffiso x.
 * @param b_z BitVector associato al suffisso z = xy.
 * @param icfl_t Lista di stringhe ICFL.
 * @param y Suffisso di z.
 * @return Punto di inserimento calcolato.
 */
unsigned int getInsertionTarget(pasta::BitVector& b_x, pasta::BitVector& b_z, std::list<std::string> &icfl_t, const std::string& y){
    unsigned int i = 0, k = 0, u = 0, p = 0, s = 0, q = 0, h = 0;
    std::string alpha;

    pasta::FlatRankSelect rs_x(b_x);
    pasta::FlatRankSelect rs_z(b_z);

    std::cout << std::endl;

    i = rs_z.select1(1);
    k = b_x.size() - 1;
    s = b_x[k] + 1;


    if(i == 0){
        u = rs_x.rank1(i) + b_x[k] + 1;
    }
    else if(i < k){
        u = rs_x.rank1(i-1) + b_x[k] + 1;
    }
    else{
        u = rs_x.rank1(b_x.size()) + 1;
    }

    p = u - 1;

    while(p > s){
        q = rs_x.select1(p - b_x[k]);
        alpha = (*find_node(icfl_t, q+1)).substr(0,y.size());
        if(alpha <= y){
            p = s - 1;
        }
        else{
            p = p - 1;
        }
    }

    //h = p + 1;
    //return h;
    return p;
}

/**
 * @brief Calcola e restituisce la lunghezza massima delle stringhe in una lista.
 *
 * Questa funzione scorre attraverso una lista di stringhe e determina la lunghezza massima tra tutte le stringhe presenti nella lista.
 *
 * @param icfl_t La lista di stringhe da esaminare.
 * @return La lunghezza massima tra tutte le stringhe nella lista.
 */
unsigned int get_maximum_length_from_factors(std::list<std::string> &icfl_t){
    unsigned int max = 0;
    auto it = icfl_t.begin();
    while(it != icfl_t.end()){
        if (it->size() > max){
            max = it->size();
        }
        ++it;
    }
    return max;
}

/**
 * @brief Restituisce la differenza tra due stringhe.
 * @param s1 La stringa da cui sottrarre.
 * @param s2 La stringa da sottrarre.
 * @return La parte di s1 che rimane dopo aver rimosso s2 dall'inizio, altrimenti s1 intera.
 *
 * Questa funzione controlla se s2 è un prefisso di s1. Se lo è, restituisce la parte di s1 che rimane
 * dopo aver rimosso il prefisso s2. Se s2 non è un prefisso di s1, restituisce s1 intera.
 */
std::string get_strings_difference(const std::string& s1, const std::string& s2) {
    if (s1.find(s2) == 0) {
        return s1.substr(s2.length());
    } else {
        return s1;
    }
}

/**
 * @brief Stampa il contenuto di una mappa con chiave stringa e valore vettore di interi.
 * @param suffix_map Mappa con chiavi di tipo std::string e valori di tipo std::vector<int>.
 *
 * Questa funzione itera attraverso una mappa e per ogni coppia chiave-valore,
 * stampa la chiave e i valori associati (un vettore di interi).
 */
void print_suffix_map(const std::unordered_map<std::string, std::vector<int>>& suffix_map) {
    for (const auto& pair : suffix_map) {
        std::cout << "Chiave: " << pair.first << ", Valori: ";
        for (const auto& value : pair.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}


/**
 * @brief Trova il nodo più profondo che ha un suffisso prefisso del suffisso dato.
 * @param node Puntatore al nodo da cui iniziare la ricerca.
 * @param suffix Il suffisso da cercare.
 * @return Puntatore al nodo più profondo il cui suffisso è un prefisso del suffisso dato.
 *
 * Questa funzione ricorsiva attraversa l'albero a partire dal nodo dato, cercando il nodo più profondo
 * il cui suffisso è un prefisso del suffisso dato. Se nessun figlio soddisfa la condizione, restituisce il nodo corrente.
 */
Node* find_deepest_prefix_node(Node* node, const std::string suffix) {
    for (Node* child : node->get_children()) {
        std::string figlio = child->get_suffix();
        if (suffix.find(figlio) == 0) {
            return find_deepest_prefix_node(child, suffix);
        }
    }
    return node;
}

/**
 * @brief Stampa l'albero a partire dal nodo specificato.
 * @param node Puntatore al nodo da cui iniziare la stampa.
 * @param prefix Prefisso della riga corrente (per formattazione).
 * @param is_last True se il nodo è l'ultimo figlio.
 */
void print_tree(Node *node, std::string prefix = "", bool is_last = true) {

    std::cout << prefix;

    if (is_last) {
        std::cout << "└── ";
        prefix += "    ";
    } else {
        std::cout << "├── ";
        prefix += "│   ";
    }

    std::cout << *node << std::endl;

    for (size_t i = 0; i < node->get_children().size(); ++i) {
        print_tree(node->get_children()[i], prefix, i == node->get_children().size() - 1);
    }

}

/**
 * @brief Costruisce un albero a partire da una lista di stringhe.
 * @param icfl_t Lista di stringhe che rappresentano i fattori da cui costruire l'albero.
 * @return L'albero costruito.
 *
 * Questa funzione costruisce un suffix tree utilizzando i fattori forniti in input. Per ogni lunghezza
 * del suffisso (da 0 alla lunghezza massima dei fattori), itera sui fattori per estrarre i suffissi
 * e aggiornare le mappe dei suffissi e dei bit. Successivamente, trova il nodo genitore più profondo
 * per ogni suffisso, determina l'insertion target e crea un nuovo nodo figlio. Il processo viene ripetuto
 * fino a completare la costruzione dell'albero.
 */
Tree build_tree(std::list<std::string>& icfl_t){
    Tree tree (icfl_t);
    Node *root = tree.get_root();
    unsigned int insertion_target = 0;

    std::unordered_map<std::string, std::vector<int>> suffix_map;
    std::unordered_map<std::string, pasta::BitVector> bit_map;

    unsigned int max_length = get_maximum_length_from_factors(icfl_t);

    for (unsigned int l = 0; l < max_length; ++l) {
        std::string suffix = "";
        unsigned int total_length = 0;

        for (unsigned int i = 0; i < icfl_t.size(); ++i) {
            std::string factor = *find_node(icfl_t, i);
            total_length += factor.size();
            unsigned int occ = 0;

            if (l < factor.length()) {
                int start = factor.length() - (l + 1);
                suffix = factor.substr(start, l + 1);
                occ = total_length - (l + 1);

                if (suffix_map.find(suffix) == suffix_map.end()) {
                    std::vector<int> suffix_g_list;
                    suffix_map.emplace(suffix, suffix_g_list);
                    suffix_map[suffix].push_back(occ);

                    // Try_emplace instead of emplace
                    bit_map.try_emplace(suffix, icfl_t.size(), 0);
                } else {
                    if (i != icfl_t.size() - 1) {
                        suffix_map[suffix].push_back(occ);
                    } else {
                        suffix_map[suffix].insert(suffix_map[suffix].begin(), occ); // push front
                    }
                }
                bit_map[suffix][i] = 1;
            }
        }

        for(auto& entry : suffix_map) {
            std::string s = entry.first;
            Node* parent = find_deepest_prefix_node(root, entry.first);

            //PRINTS FOR DEBUGGING
            /*
            std::cout << s << " & " << parent->get_suffix() << " = " << get_strings_difference(s, parent->get_suffix()) << std::endl;
            print_bv(*(parent->get_bv_pointer()));
            print_bv(bit_map[s]);
            //print_list(icfl_t);
            */

            insertion_target = getInsertionTarget(*parent->get_bv_pointer(), bit_map[s], icfl_t,
                                                  get_strings_difference(s, parent->get_suffix()));

            std::pair<unsigned int, unsigned int> indexes(suffix_map[s][0], suffix_map[s][0] + (l + 1));
            Node *child = new Node(root, parent, {}, indexes, entry.second, insertion_target, &bit_map[s]);
            parent->add_child(child);
            child->print_data();

            //clear the buffer
            std::cout << std::endl;
        }

        bit_map.clear();
        suffix_map.clear();
    }

    return tree;
}

/**
 * @brief Costruisce una lista inserendo la g-list di ogni nodo nella g-list del nodo genitore.
 *
 * La funzione viene chiamata ricorsivamente per ogni nodo e i suoi figli,
 * inserendo la g-list di ciascun nodo nella g-list del nodo genitore in una posizione specificata.
 * La g-list della radice dell'albero corrisponderà al suffix-array.
 *
 * @param node Puntatore al nodo corrente.
 */
void build_list(Node* node) {
    for (int i = node->get_children().size() - 1; i >= 0; i--) {
        build_list(node->get_children()[i]);
    }

    //PRINTS FOR DEBUGGING
    //std::cout << " ------------ " << std::endl;
    //std::cout << "analyzing " << node->get_suffix() << "..."  << std::endl;

    unsigned int h = node->get_insertion_target();
    //std::cout << "insertion target: " << h << std::endl;

    Node* parent = node->get_parent();
    if (parent == nullptr) {
        std::cout << "Parent node is null" << std::endl;
        return;
    }

    std::vector<int>& parent_g_list = parent->get_g_list();
    std::vector<int>& node_g_list = node->get_g_list();

    std::vector<int>::iterator it = parent_g_list.begin();
    std::advance(it, h);

    //std::cout << "printing before: parent ";
    //print_g_list_vector(parent_g_list);
    //std::cout << "child: ";
    //print_g_list_vector(node_g_list);

    //insertion
    parent_g_list.insert(it, node_g_list.begin(), node_g_list.end());
    std::cout << "printing " << node->get_parent()->get_suffix() << " list: ";
    print_g_list_vector(parent_g_list);
}











