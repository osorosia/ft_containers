#include "_test.hpp"

void vector_empty_test() {
    TODO();
    ft::vector< int > vec;
    assert(vec.empty());
}

void vector_size_test() {
    TODO();
    ft::vector< int > vec;
    assert(vec.size() == 0);
}

void vector_op_eq_test() { TODO(); }
void vector_op_ne_test() { TODO(); }
void vector_op_lt_test() { TODO(); }
void vector_op_le_test() { TODO(); }
void vector_op_gt_test() { TODO(); }
void vector_op_ge_test() { TODO(); }

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
    vector_size_test();
    // Modifiers

    //
    // Non member functions
    //
    vector_op_eq_test();
    vector_op_ne_test();
    vector_op_lt_test();
    vector_op_le_test();
    vector_op_gt_test();
    vector_op_ge_test();

    OK();
}
