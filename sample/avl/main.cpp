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

int main() {
    AVLTree tree;

    struct {
        string op;
        long   val;
    } cases[] = {
        {"insert", 10},
        {"insert", 1},
        {"insert", 2},
        {"insert", 0},
        {"insert", 15},
        {"insert", 12},
        {"insert", 11},
        {"insert", 13},
        {"insert", 20},
        {"insert", 18},
        {"erase", 15},
        {"erase", 13},
        {"erase", 12},
        {"erase", 10},
        {"erase", 11},
        {"erase", 1},
        {"erase", 21},
        {"erase", 20},
        {"erase", 18},
        {"erase", 0},
        {"erase", 2},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        if (cases[i].op == "insert")
            tree.insert(cases[i].val);
        else if (cases[i].op == "erase")
            tree.erase(cases[i].val);

        cout << "# " << cases[i].op << ": " << cases[i].val << endl;
        print(tree);
    }
    tree.clear();

    cout << "# finish" << endl;

    // printAndCheck(tree);

    // tree.erase(15);
    // printAndCheck(tree);

    // OK(checkAVL(tree));
}
