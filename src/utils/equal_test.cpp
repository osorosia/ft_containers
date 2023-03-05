#include "../_test.hpp"

// bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
void equal_template0_test() {
    std::vector< int > vec0;
    std::vector< int > vec1;
    for (int i = 0; i < 3; i++) {
        vec0.push_back(i);
        vec1.push_back(i);
    }

    // vec0 = {0, 1, 2}
    // vec1 = {0, 1, 2}
    assert(ft::equal(vec0.begin(), vec0.end(), vec1.begin()));

    // vec0 = {0, 1, 2, 10}
    // vec1 = {0, 1, 2, 11}
    vec0.push_back(10);
    vec1.push_back(11);
    assert(!ft::equal(vec0.begin(), vec0.end(), vec1.begin()));
}

// template < class T >
bool binary_pred(int x, int y) { return x == y; }

// bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);
void equal_template1_test() {
    std::vector< int > vec0;
    std::vector< int > vec1;
    for (int i = 0; i < 3; i++) {
        vec0.push_back(i);
        vec1.push_back(i);
    }
    // vec0 = {0, 1, 2}
    // vec1 = {0, 1, 2}
    assert(ft::equal(vec0.begin(), vec0.end(), vec1.begin(), binary_pred));

    // vec0 = {0, 1, 2, 10}
    // vec1 = {0, 1, 2, 11}
    vec0.push_back(10);
    vec1.push_back(11);
    assert(!ft::equal(vec0.begin(), vec0.end(), vec1.begin(), binary_pred));
}

void equal_test() {
    TEST_NAME("equal");

    // bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
    equal_template0_test();
    // bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);
    equal_template1_test();

    OK();
}
