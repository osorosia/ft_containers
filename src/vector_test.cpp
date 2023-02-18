#include "_test.hpp"

void vector_constructor_test() { TODO(); }
void vector_destructor_test() { TODO(); }
void vector_op_assign_test() { TODO(); }
void vector_assign_test() { TODO(); }
void vector_get_allocator_test() { TODO(); }

void vector_at_test() {
    ft::vector< int > ft_vec;
    std::vector<int > std_vec;
    for (int i = 0; i < 3; i++) {
        ft_vec.push_back(i + 1);
        std_vec.push_back(i + 1);
    }
    assert(ft_vec.at(0) == std_vec.at(0));
    assert(ft_vec.at(1) == std_vec.at(1));
    assert(ft_vec.at(2) == std_vec.at(2));
    
    try {
        ft_vec.at(3);
        assert(false);
    } catch (std::out_of_range e) {
    }
    try {
        std_vec.at(3);
        assert(false);
    } catch (std::out_of_range e) {
    }

    try {
        ft_vec.at(-1);
        assert(false);
    } catch (std::out_of_range e) {
    }
    try {
        std_vec.at(-1);
        assert(false);
    } catch (std::out_of_range e) {
    }

    // TODO: const

    // const ft::vector<int> c_vec = vec;
    // vec.push_back(3);
}

void vector_op_at_test() {
    ft::vector< int > ft_vec;
    std::vector<int > std_vec;
    for (int i = 0; i < 3; i++) {
        ft_vec.push_back(i + 1);
        std_vec.push_back(i + 1);
    }
    assert(ft_vec[0] == std_vec[0]);
    assert(ft_vec[1] == std_vec[1]);
    assert(ft_vec[2] == std_vec[2]);

    // TODO: const
}
void vector_front_test() {
    ft::vector<int> ft_vec;
    ft::vector<int> std_vec;
    for (int i = 0; i < 3; i++) {
        ft_vec.push_back(i + 1);
        std_vec.push_back(i + 1);
    }
    

    // TODO: const
}
void vector_back_test() { TODO(); }
void vector_data_test() { TODO(); }

void vector_begin_test() { TODO(); }
void vector_end_test() { TODO(); }
void vector_rbegin_test() { TODO(); }
void vector_rend_test() { TODO(); }

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
void vector_max_size_test() { TODO(); }
void vector_reserve_test() { TODO(); }
void vector_capacity_test() { TODO(); }

void vector_clear_test() { TODO(); }
void vector_insert_test() { TODO(); }
void vector_erase_test() { TODO(); }
void vector_push_back_test() { TODO(); }
void vector_pop_back_test() { TODO(); }
void vector_resize_test() { TODO(); }
void vector_swap_test() { TODO(); }

void vector_op_eq_test() { TODO(); }
void vector_op_ne_test() { TODO(); }
void vector_op_lt_test() { TODO(); }
void vector_op_le_test() { TODO(); }
void vector_op_gt_test() { TODO(); }
void vector_op_ge_test() { TODO(); }

void vector_normal_test() {
    ft::vector< int > vec;
    assert(vec.size() == 0);

    vec.push_back(1);
    assert(vec.size() == 1);
}

void vector_test() {
    TEST_NAME("vector");

    vector_normal_test();

    //
    // Member functions
    //
    vector_constructor_test();
    vector_destructor_test();
    vector_op_assign_test();
    vector_assign_test();
    vector_get_allocator_test();

    // Element access
    vector_at_test();
    vector_op_at_test();
    vector_front_test();
    vector_back_test();
    vector_data_test();

    // Iterator
    vector_begin_test();
    vector_end_test();
    vector_rbegin_test();
    vector_rend_test();

    // Capacity
    vector_empty_test();
    vector_size_test();
    vector_max_size_test();
    vector_reserve_test();
    vector_capacity_test();

    // Modifiers
    vector_clear_test();
    vector_insert_test();
    vector_erase_test();
    vector_push_back_test();
    vector_pop_back_test();
    vector_resize_test();
    vector_swap_test();

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
