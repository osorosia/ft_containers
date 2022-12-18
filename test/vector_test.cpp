#include "test.hpp"

void vector_constructor() {
    CASE_NAME("vector_constructor");
    TODO();
}

void vector_destructor() {
    CASE_NAME("vector_destructor");
    TODO();
}

void vector_operator_assign() {
    CASE_NAME("vector_operator_assign");
    TODO();
}

void vector_assign() {
    CASE_NAME("vector_assign");
    TODO();
}

void vector_get_allocator() {
    CASE_NAME("vector_get_allocator");
    TODO();
}

void vector_at() {
    CASE_NAME("vector_at");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(1, vec.at(0));
    OK(2, vec.at(1));
    OK(3, vec.at(2));

    try {
        vec.at(-1);
        RESULT(false);
    } catch (std::exception& e) {
        RESULT(true);
    }

    try {
        vec.at(vec.size());
        RESULT(false);
    } catch (std::exception& e) {
        RESULT(true);
    }
}

void vector_operator_access() {
    CASE_NAME("vector_operator_access");
    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(1, vec[0]);
    OK(2, vec[1]);
    OK(3, vec[2]);
}

void vector_front() {
    CASE_NAME("vector_front");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(1, vec.front());
    vec.push_back(4);
    OK(1, vec.front());
}

void vector_back() {
    CASE_NAME("vector_back");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(3, vec.back());
    vec.push_back(4);
    OK(4, vec.back());
}

void vector_data() {
    CASE_NAME("vector_data");
    TODO();
}

void vector_begin() {
    CASE_NAME("vector_begin");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(1, *vec.begin());
    OK(2, *(vec.begin() + 1));
    OK(3, *(vec.begin() + 2));
}

void vector_end() {
    CASE_NAME("vector_end");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(3, *(vec.end() - 1));
    OK(2, *(vec.end() - 2));
    OK(1, *(vec.end() - 3));
}

void vector_rbegin() {
    CASE_NAME("vector_rbegin");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(3, *(vec.rbegin()));
    OK(2, *(vec.rbegin() + 1));
    OK(1, *(vec.rbegin() + 2));
}

void vector_rend() {
    CASE_NAME("vector_rend");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(1, *(vec.rend() - 1));
    OK(2, *(vec.rend() - 2));
    OK(3, *(vec.rend() - 3));
}

void vector_empty() {
    CASE_NAME("vector_empty");

    vector< int > vec;
    OK(true, vec.empty());
    vec.push_back(1);
    OK(false, vec.empty());
}

void vector_size() {
    CASE_NAME("vector_size");

    vector< int > vec;
    OK((size_t)0, vec.size());

    vec.push_back(1);
    OK((size_t)1, vec.size());

    vec.push_back(2);
    OK((size_t)2, vec.size());

    vec.push_back(3);
    OK((size_t)3, vec.size());
}

void vector_max_size() {
    CASE_NAME("vector_max_size");
    vector< int > vec;

    size_t sz = vec.max_size();
    vec.push_back(1);
    OK(sz, vec.max_size());

    std::cout << MAGENTA << "max_size=" << vec.max_size() << END;
}

void vector_reserve() {
    CASE_NAME("vector_reserve");

    vector< int > vec;

    size_t sz = vec.capacity();
    vec.reserve(10);
    OK(sz + 10, vec.capacity());

    try {
        vec.reserve(vec.max_size());
        RESULT(false);
    } catch (std::exception& e) {
        RESULT(true);
        OK(std::string("std::bad_alloc"), std::string(e.what()));
    }

    OK(sz + 10, vec.capacity());
}

void vector_capacity() {
    CASE_NAME("vector_capacity");
    TODO();
}

void vector_clear() {
    CASE_NAME("vector_clear");
    TODO();
}

void vector_insert() {
    CASE_NAME("vector_insert");
    TODO();
}

void vector_erase() {
    CASE_NAME("vector_erase");
    TODO();
}

void vector_push_back() {
    CASE_NAME("vector_push_back");
    TODO();
}

void vector_pop_back() {
    CASE_NAME("vector_pop_back");
    TODO();
}

void vector_resize() {
    CASE_NAME("vector_resize");

    vector< int > vec;
    OK(0, vec.size());

    vec.resize(3);
    OK(3, vec.size());
    OK(0, vec[0]);
    OK(0, vec[1]);
    OK(0, vec[2]);

    vec.resize(5, 42);
    OK(5, vec.size());
    OK(0, vec[0]);
    OK(0, vec[1]);
    OK(0, vec[2]);
    OK(42, vec[3]);
    OK(42, vec[4]);
}

void vector_swap() {
    CASE_NAME("vector_swap");
    TODO();
}

void vector_operator_eq() {
    CASE_NAME("vector_operator_eq");

    vector< int > vec0;
    vec0.push_back(1);
    vec0.push_back(2);
    vec0.push_back(3);
    vector< int > vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    OK(true, vec0 == vec1);

    vec0.push_back(1);
    OK(false, vec0 == vec1);
    vec1.push_back(1);
    OK(true, vec0 == vec1);

    vec0.push_back(5);
    OK(false, vec0 == vec1);
    vec1.push_back(42);
    OK(false, vec0 == vec1);
}

void vector_operator_ne() {
    CASE_NAME("vector_operator_ne");

    vector< int > vec0;
    vec0.push_back(1);
    vec0.push_back(2);
    vec0.push_back(3);
    vector< int > vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    OK(false, vec0 != vec1);

    vec0.push_back(1);
    OK(true, vec0 != vec1);
    vec1.push_back(1);
    OK(false, vec0 != vec1);

    vec0.push_back(5);
    OK(true, vec0 != vec1);
    vec1.push_back(42);
    OK(true, vec0 != vec1);
}

void vector_operator_lt() {
    CASE_NAME("vector_operator_lt");
    TODO();
}

void vector_operator_le() {
    CASE_NAME("vector_operator_le");
    TODO();
}

void vector_operator_gt() {
    CASE_NAME("vector_operator_gt");
    TODO();
}

void vector_operator_ge() {
    CASE_NAME("vector_operator_ge");
    TODO();
}

void vector_test() {
    TEST_NAME("vector_test");

    vector_constructor();
    vector_destructor();
    vector_operator_assign();
    vector_assign();
    vector_get_allocator();

    // Element access
    vector_at();
    vector_operator_access();
    vector_front();
    vector_back();
    vector_data();

    // Iterators
    vector_begin();
    vector_end();
    vector_rbegin();
    vector_rend();

    // Capacity
    vector_empty();
    vector_size();
    vector_max_size();
    vector_reserve();
    vector_capacity();

    // Modifiers
    vector_clear();
    vector_insert();
    vector_erase();
    vector_push_back();
    vector_pop_back();
    vector_resize();
    vector_swap();

    // operator
    vector_operator_eq(); // ==
    vector_operator_ne(); // !=
    vector_operator_lt(); // <
    vector_operator_le(); // <=
    vector_operator_gt(); // >
    vector_operator_ge(); // >=

    TEST_END();
}
