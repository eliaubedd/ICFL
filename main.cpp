#include "func.hpp"

int main()
{
    //Create text
    std::list<std::string> icfl_text = build_ICFL();
    std::cout << "Sia ICFL(T) =" ; print_list(icfl_text);

    //Create suffix
    std::string x = "a";
    std::string z = "abca";
    std::string y = "bca";
    std::cout << "Siano x = " << x << " e z = xy = " << z << std::endl;

    //Create x and z list
    std::list<int> xgList = build_xgList();
    std::list<int> zgList = build_zgList();
    std::cout << "[x]_g-list = "; print_list(xgList);
    std::cout << "[z]_g-list = "; print_list(zgList);

    //Create a bit vectors
    pasta::BitVector bv_x(4, 1);
    pasta::BitVector bv_z(4,0);
    bv_z[2] = 1;
    bv_z[3] = 1;
    std::cout << "bit vector Bx: "; print_bv(bv_x);
    std::cout << "bit vector Bz: "; print_bv(bv_z);

    std::cout << *find_node(icfl_text, 3) << std::endl;
    unsigned int h = getInsertionTarget(bv_x, bv_z, icfl_text, y);
    std::cout << "Insertion target h: " << h << std::endl;
    std::cout << "Nodo dell'insertion target: " << *find_node(xgList, h) << std::endl;

    std::list<std::string> prova = read_text_data("../input.txt");
    print_list(prova);
    return 0;

}