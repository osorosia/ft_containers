#include "_test.hpp"

int main() {
    pair_test();
    vector_test();

    // utils
    enable_if_test();
    equal_test();
    is_integral_test();
    iterator_traits_test();
    lexicographical_compare_test();
    reverse_iterator_test();
}
