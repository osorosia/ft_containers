#include "avl.hpp"
#include "config.hpp"
#include <iostream>
#include <random>

using namespace std;

void print(AVLTree& tree);
void check(AVLTree& tree);

void NG(bool b) {
    if (b)
        return;
    cout << "```" << endl;
    cout << "███    ██  ██████ " << endl;
    cout << "████   ██ ██      " << endl;
    cout << "██ ██  ██ ██   ███" << endl;
    cout << "██  ██ ██ ██    ██" << endl;
    cout << "██   ████  ██████ " << endl;
    cout << "```" << endl;
}

void test() {
    mt19937 mt((int)time(0));
    AVLTree tree;

    for (int i = 0; i < 10; i++) {
        // insert
        for (int j = 0; j < 20; j++) {
            tree.insert(mt() % 20 + 1);
            check(tree);
        }
        // erase
        for (int j = 0; j < 10; j++) {
            tree.erase(mt() % 20 + 1);
            check(tree);
        }
    }
}

int main() {
    AVLTree tree;

    struct {
        string op;
        long   val;
    } cases[] = {
        {"insert", 10}, {"insert", 1},  {"insert", 2},  {"insert", 0},  {"insert", 15},
        {"insert", 12}, {"insert", 11}, {"insert", 13}, {"insert", 20}, {"insert", 18},
        {"erase", 15},  {"erase", 13},  {"erase", 12},  {"erase", 10},  {"erase", 11},
        {"erase", 1},   {"erase", 21},  {"erase", 20},  {"erase", 18},  {"erase", 0},
        {"erase", 2},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        if (cases[i].op == "insert")
            tree.insert(cases[i].val);
        else if (cases[i].op == "erase")
            tree.erase(cases[i].val);

        cout << "# " << cases[i].op << ": " << cases[i].val << endl;
        tree.print();
        check(tree);
    }
    tree.clear();

    cout << "# finish" << endl;

    test();
}
