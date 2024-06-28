#include "func.hpp"
#include "tree.hpp"
#include "node.hpp"

#include <string>
//run this command for leaks: leaks -atExit -- cmake-build-debug/ICFL

/*
void test_node_creation() {
    Node root;
    root.set_text("banana");

    Node child(&root, &root, {}, std::make_pair(1, 6), {0, 1, 2}, 1, nullptr);
    root.add_child(&child);

    std::cout << "Test Node Creation:" << std::endl;
    root.print_data();
    child.print_data();
    std::cout << std::endl;
}

void test_tree_creation() {
    Tree suffix_tree("banana");
    Node* root = suffix_tree.get_root();

    Node* child = new Node(root, root, {}, std::make_pair(1, 6), {0, 1, 2}, 1, nullptr);
    root->add_child(child);

    std::cout << "Test Tree Creation:" << std::endl;
    root->print_data();
    child->print_data();
    std::cout << std::endl;

    delete child;
}

void test_bitvector() {
    pasta::BitVector bv(6, 0);
    bv[1] = 1;
    bv[3] = 1;
    bv[5] = 1;

    Node root;
    root.set_text("banana");
    Node child(&root, &root, {}, std::make_pair(1, 6), {0, 1, 2}, 1, &bv);

    std::cout << "Test BitVector:" << std::endl;
    root.print_data();
    child.print_data();
    std::cout << std::endl;
}

void test_comparisons() {
    Node root;
    root.set_text("banana");

    Node child1(&root, &root, {}, std::make_pair(1, 6), {0, 1, 2}, 1, nullptr);
    Node child2(&root, &root, {}, std::make_pair(2, 6), {0, 1, 2}, 1, nullptr);

    std::cout << "Test Comparisons:" << std::endl;
    root.add_child(&child1);
    root.add_child(&child2);
    root.print_data();
    child1.print_data();
    child2.print_data();
    std::cout << std::endl;
}
 */
int main()
{

    std::list<std::string> icfl_t = build_input_ICFL("../input.txt");
    std::cout << "ICFL(T) from input.txt: ";
    print_list(icfl_t); std::cout << std::endl;

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

    /*
    //Create a bit vectors
    pasta::BitVector bv_x(4, 1);
    pasta::BitVector bv_z(4, 0);
    bv_z[2] = 1;
    bv_z[3] = 1;
    std::cout << "bit vector Bx: "; print_bv(bv_x);
    std::cout << "bit vector Bz: "; print_bv(bv_z);
    unsigned int h = getInsertionTarget(bv_x, bv_z, icfl_t, get_strings_difference("abca", "a"));
    std::cout << "Insertion target h: " << h << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << get_strings_difference("ciao", "ci") << std::endl;
    */
    //std::string t = build_text_from_ICFL(icfl_t);

    Tree tree = build_tree(icfl_t);
    std::cout << "STAMPA ALBERO: " << std::endl;
    print_tree(tree.get_root());



    return 0;

}