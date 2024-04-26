/**
 * @file funch.cpp
 * @brief Contiene le funzioni di supporto per BitVector e List, .
 */

#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <iostream>
#include <list>
#include <string>

/**
 * @brief Costruisce e restituisce una lista di stringhe di esempio.
 *
 * Costruisce una lista di stringhe di esempio e la restituisce.
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
    std::cout << " < ";
    for (const T& x : list) {
        std::cout << x << " ";
    }
    std::cout << "> " << std::endl;
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
 * @param y Suffisso di x.
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