#include "../src/_test.hpp"

int main() {
    vector_test();
    map_test();
    pair_test();

    // utils
    enable_if_test();
    equal_test();
    is_integral_test();
    iterator_traits_test();
    lexicographical_compare_test();
    reverse_iterator_test();

    // tree
    avl_tree_test();
}
