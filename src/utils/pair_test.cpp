#include "../_test.hpp"

void pair_constructor_test() {
    ft::pair< int, int > x(1, 2);
    assert(x.first == 1);
    assert(x.second == 2);

    ft::pair< int, int > y(x);
    assert(y.first == x.first);
    assert(y.second == x.second);
}

void pair_operator_eq_test() {
    ft::pair< int, int > x;
    x.first  = 1;
    x.second = 2;

    ft::pair< int, int > cp_x;
    cp_x = x;

    assert(cp_x.first == x.first);
    assert(cp_x.second == x.second);
}

void pair_operator_comp_test() {
    ft::pair< int, int >  ft0(0, 0);
    std::pair< int, int > std0(0, 0);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            ft::pair< int, int >  ft1(i, j);
            std::pair< int, int > std1(i, j);

            assert((ft0 == ft1) == (std0 == std1));
            assert((ft0 != ft1) == (std0 != std1));
            assert((ft0 < ft1) == (std0 < std1));
            assert((ft0 <= ft1) == (std0 <= std1));
            assert((ft0 > ft1) == (std0 > std1));
            assert((ft0 >= ft1) == (std0 >= std1));
        }
    }
}

void make_pair_test() {
    ft::pair< int, int > x = ft::make_pair(1, 2);
    assert(x.first == 1);
    assert(x.second == 2);
}

void pair_test() {
    TEST_NAME("pair");
    pair_constructor_test();
    pair_operator_eq_test();
    pair_operator_comp_test();
    make_pair_test();
    OK();
}
