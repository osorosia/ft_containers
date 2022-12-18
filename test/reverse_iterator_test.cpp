#include "test.hpp"

void reverse_iterator_test() {
    TEST_NAME("reverse_iterator_test");

    std::vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    reverse_iterator< decltype(vec)::iterator > first(vec.end());
    reverse_iterator< decltype(vec)::iterator > last(vec.begin());

    OK(5, *(first++));
    OK(4, *(first++));
    OK(3, *(first++));
    OK(2, *(first++));
    OK(1, *(first++));
    OK(last, first);

    TEST_END();
}
