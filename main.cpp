#include "func.hpp"

#include <string>

int main()
{
    //Create text
    std::list<std::string> icfl_text = build_input_ICFL("../input.txt");
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

    unsigned int h = getInsertionTarget(bv_x, bv_z, icfl_text, y);
    std::cout << "Insertion target h: " << h << std::endl;
    std::cout << "Nodo dell'insertion target: " << *find_node(xgList, h) << std::endl;

    std::cout << "-----------" << std::endl;

    tree<std::string> tr;
    tree<std::string>::iterator top, one, two, loc, banana;

    top=tr.begin();
    one=tr.insert(top, "one");
    two=tr.append_child(one, "two");
    tr.append_child(two, "apple");
    banana=tr.append_child(two, "banana");
    tr.append_child(banana,"cherry");
    tr.append_child(two, "peach");
    tr.append_child(one,"three");

    print_tree(tr, tr.begin());

    std::cout << "-----------" << std::endl;
    std::cout << "max length: " << get_maximum_length_from_factors(icfl_text) << std::endl;
    std::cout << build_text_from_ICFL(icfl_text) << std::endl;
    //build_tree(icfl_text);
    std::vector<int> v = {1, 2, 3, 4, 5};
    v.insert(v.begin(), 100);
    return 0;

}