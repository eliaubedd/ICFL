#include "func.hpp"
#include "tree.hpp"
#include "node.hpp"

#include <string>
//run this command or leaks: leaks -atExit -- cmake-build-debug/ICFL
void test_tree_creation() {
    Tree tree;
    std::cout << "Test Tree Creation: Passed" << std::endl;
}

void test_node_insertion() {
    Tree tree;
    Node root(nullptr, nullptr, {}, std::make_pair(0, 0), {}, 0, nullptr, "banana");

    Node node1(&root, &root, {}, std::make_pair(0, 3), {}, 0, nullptr);  // e.g., "ban"
    Node node2(&root, &root, {}, std::make_pair(3, 6), {}, 0, nullptr);  // e.g., "ana"

    root.add_child(&node1);
    root.add_child(&node2);

    std::cout << root.get_text() << std::endl; print_tree(&root); // Should show the structure of the tree with nodes "ban" and "ana"

    std::cout << "Test Node Insertion: Passed" << std::endl;
}

/*
void test_suffix_retrieval() {
    Tree tree("banana", *(new Node()));
   // Node* node = new Node(&tree, nullptr, {}, {0, 3}, {}, 0, nullptr); // "ban"
   Node node()

    std::string suffix = node->get_suffix();
    std::cout << "Retrieved Suffix: " << suffix << std::endl; // Should output "ban"

    if (suffix == "ban") {
        std::cout << "Test Suffix Retrieval: Passed" << std::endl;
    } else {
        std::cout << "Test Suffix Retrieval: Failed" << std::endl;
    }
}

void test_tree_printing() {
    Tree tree("banana", *(new Node()));
    Node* root = new Node(&tree, nullptr, {}, {0, 0}, {}, 0, nullptr);

    Node* node1 = new Node(&tree, root, {}, {0, 3}, {}, 0, nullptr);  // "ban"
    Node* node2 = new Node(&tree, root, {}, {3, 6}, {}, 0, nullptr);  // "ana"

    root->add_child(node1);
    root->add_child(node2);

    print_tree(root); // Should print the structure of the tree

    std::cout << "Test Tree Printing: Passed" << std::endl;
}
*/
int main()
{

    std::list<std::string> icfl_t = build_input_ICFL("../input.txt");
    //Create suffix
    /*
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
    pasta::BitVector bv_z(4, 0);
    std::cout << "bit vector Bx: "; print_bv(bv_x);
    std::cout << "bit vector Bz: "; print_bv(bv_z);
    unsigned int h = getInsertionTarget(bv_x, bv_z, icfl_t, y);
    std::cout << "Insertion target h: " << h << std::endl;
    std::cout << "Nodo dell'insertion target: " << *find_node(xgList, h) << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << get_strings_difference("ciao", "ci") << std::endl;

    */
    Tree tree = build_tree(icfl_t);
    //print_tree(tree.get_root());


    return 0;

}