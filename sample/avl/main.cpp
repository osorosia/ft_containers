#include "avl.hpp"
#include <iostream>
using namespace std;

void print(AVLTree& tree);
bool checkAVL(AVLTree& tree);

void OK(bool b) { cout << (b ? "OK" : "NG!!!!!") << endl; }

int main() {
    AVLTree tree;
    tree.insert(0);
    tree.insert(1);
    tree.insert(2);

    print(tree);
    OK(checkAVL(tree));

    // tree.erase(1);
}
