#include "avl.hpp"
#include <iostream>
using namespace std;

void print(AVLTree& tree);
bool checkAVL(AVLTree& tree);

void OK(bool b) { cout << "# " << (b ? "OK" : "NG!!!!!") << endl; }

void printAndCheck(AVLTree& tree) {
    OK(checkAVL(tree));
    print(tree);
}

void test() {
    {
        AVLTree tree;
        long    data[] = {0, 1, 2};
        for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
            tree.insert(data[i]);
        }
    }
}

int main() {
    // test();
    AVLTree tree;
    long    data[] = {10, 1, 2, 0, 15, 12, 11, 13, 20, 18};
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        tree.insert(data[i]);
    }

    printAndCheck(tree);

    // tree.erase(15);
    // printAndCheck(tree);

    // OK(checkAVL(tree));
    // tree.erase(1);
}
