#include "test.hpp"

void iterator_traits_test() {
    TEST_NAME("iterator_traits_test");

    std::vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    iterator_traits< decltype(vec)::iterator >::difference_type n;

    TEST_END();
}
