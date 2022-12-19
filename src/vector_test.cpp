#include "_test.hpp"

void vector_empty_test() {
    TODO();
    ft::vector<int> vec;
    assert(vec.empty());
}

void vector_test() {
    TEST_NAME("vector");

    //
    // Member functions
    //
    // (Non title)
    // Element access
    // Iterator
    // Capacity
    vector_empty_test();
    // Modifiers

    //
    // Non member functions
    //

    OK();
}
