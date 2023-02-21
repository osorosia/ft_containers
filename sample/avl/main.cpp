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
    struct {
        string op;
        long   val;
    } cases[] = {
        {"insert", 10}, {"insert", 1},  {"insert", 2},  {"insert", 0},
        {"insert", 15}, {"insert", 12}, {"insert", 11}, {"insert", 13},
        {"insert", 20}, {"insert", 18}, {"erase", 15},
    };
    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        if (cases[i].op == "insert")
            tree.insert(cases[i].val);
        else if (cases[i].op == "erase")
            tree.erase(cases[i].val);

        cout << "# " << cases[i].op << ": " << cases[i].val << endl;
        print(tree);
    }
    // cout << "# " << "finish" << endl;
    // print(tree);

    // printAndCheck(tree);

    // tree.erase(15);
    // printAndCheck(tree);

    // OK(checkAVL(tree));
    // tree.erase(1);
}
