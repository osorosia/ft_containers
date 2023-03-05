#include "../_test.hpp"
#include <string>

void avl_normal_test() {
    ft::AvlTree< int, int >      tree;
    typedef ft::pair< int, int > value_type;

    struct {
        std::string op;
        int         val;
    } cases[] = {
        {"insert", 10}, {"insert", 1},  {"insert", 2},  {"insert", 0},  {"insert", 15},
        {"insert", 12}, {"insert", 11}, {"insert", 13}, {"insert", 20}, {"insert", 18},
        {"erase", 15},  {"erase", 13},  {"erase", 12},  {"erase", 10},  {"erase", 11},
        {"erase", 1},   {"erase", 21},  {"erase", 20},  {"erase", 18},  {"erase", 0},
        {"erase", 2},
    };

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        std::cout << "# " << cases[i].op << " " << cases[i].val << std::endl;
        if (cases[i].op == "insert") {
            value_type val = value_type(cases[i].val, i);
            tree.insert(val);
        } else if (cases[i].op == "erase") {
            tree.erase(cases[i].val);
        }
        tree.print();
        tree.check();
    }
}

void avl_tree_test() {
    TEST_NAME("avl_tree");

    avl_normal_test();

    OK();
}
