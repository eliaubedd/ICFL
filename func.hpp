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
void print_bv(pasta::BitVector &bv){
    for (auto &it : bv){
        std::cout << (it ? '1' : '0');
    }
    std::cout << std::endl;
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
unsigned int getInsertionTarget(pasta::BitVector& b_x, pasta::BitVector& b_z, std::list<std::string> &icfl_t, std::string y){
    unsigned int i = 0, k = 0, u = 0, p = 0, s = 0, q = 0, h = 0;
    std::string alpha;

    pasta::FlatRankSelect rs_x(b_x);
    pasta::FlatRankSelect rs_z(b_z);

    i = rs_z.select1(1);
    k = b_x.size();
    s = b_x[k] + 1;

    if(i < k){
        u = rs_z.rank1(i-1) + b_x[k] + 1;
    }
    else{
        u = rs_z.rank1(b_z.size()) + 1;
    }

    p = u - 1;

    while(p >= s){
        q = rs_x.select1(p - b_x[k]);
        alpha = (*find_node(icfl_t, q+1)).substr(0,y.size());
        if(alpha <= y){
            p = s - 1;
        }
        else{
            p = p - 1;
        }
    }

    h = p + 1;
    return h;
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
 * @brief Stampa una rappresentazione ad albero di una struttura ad albero.
 *
 * Questa funzione stampa una rappresentazione visuale di un albero a partire da un iteratore specificato.
 * La funzione utilizza una stringa di spazi per mantenere la struttura dell'albero e indicare le relazioni padre-figlio.
 *
 *
 * @tparam T Il tipo degli elementi memorizzati nell'albero.
 * @param tr La struttura ad albero da stampare.
 * @param it L'iteratore al nodo corrente dell'albero.
 * @param blank Una stringa utilizzata per mantenere l'indentazione dei nodi dell'albero (default è una stringa vuota).
 * @param last_child Un booleano che indica se il nodo corrente è l'ultimo figlio (default è false).
 */
template<typename T>
void print_tree(const tree<T>& tr, typename tree<T>::iterator it, std::string blank = "", bool last_child = false) {
    auto child = tr.begin(it);
    auto last = tr.end(it);
    --last;

    if (it != tr.begin()) {
        std::cout << blank;
        if (last_child) {
            std::cout << "└── ";
            blank.append("    ");
        } else {
            std::cout << "├── ";
            blank.append("│   ");
        }
    }

    std::cout << *it << std::endl;

    while (child != tr.end(it)) {
        print_tree(tr, child, blank, child == last);
        ++child;
    }
}

template<typename T>
void build_tree(std::list<T> &icfl_t) {
    unsigned int max_length = get_maximum_length_from_factors(icfl_t);

    for (int l = 0; l < max_length; ++l) {
        std::unordered_map<std::string, std::vector<int>> suffix_map;
        std::unordered_map<std::string, pasta::BitVector*> bit_map;
        std::string suffix = "";
        unsigned int total_length = 0;

        for (int i = 0; i < icfl_t.size(); ++i) {
            std::string factor = *find_node(icfl_t, i);
            total_length = total_length + factor.size();
            unsigned int occ = 0;

            if (l < factor.length()) {
                int start = factor.length() - (l+1) - 1;
                suffix = factor.substr(start, l+1);
                occ = total_length - (l+1);

                if(suffix_map.find(suffix) == suffix_map.end()){
                    std::vector<int> suffix_g_list;
                    pasta::BitVector B_s(icfl_t.size(), 0);
                    print_bv(B_s);

                    suffix_map.insert(std::make_pair(suffix, suffix_g_list));
                    suffix_map[suffix].push_back(occ);

                    //TODO EMPLACE
                    bit_map.insert(std::make_pair(suffix, &B_s));
                }
                else{
                    //TODO

                }
            }
        }

        // Pulizia della memoria allocata dinamicamente
        for (auto& pair : bit_map) {
            delete pair.second;
        }
    }
}








