#include "_test.hpp"

typedef ft::vector< int >  ft_vector;
typedef std::vector< int > std_vector;

typedef std::allocator< int > allocater;

void vector_test() {
    TEST_NAME("vector");

    // --------------------------------------------------------
    // (constructor)
    // --------------------------------------------------------
    // operator=
    // --------------------------------------------------------
    // assign
    // --------------------------------------------------------
    // get_allocator
    // --------------------------------------------------------
    // at, operator[], front, back
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        int left  = 0;
        int right = 10;

        for (int i = left; i < right; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);
            assert(ft_vec.front() == std_vec.front());
            assert(ft_vec.back() == std_vec.back());
        }

        for (int i = left; i < right; i++) {
            assert(ft_vec[i] == std_vec[i]);
            assert(ft_vec.at(i) == std_vec.at(i));
        }

        try {
            ft_vec.at(left - 1);
            assert(false);
        } catch (std::out_of_range e) {
        }
        try {
            ft_vec.at(right);
            assert(false);
        } catch (std::out_of_range e) {
        }
    }
    // --------------------------------------------------------
    // data
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);
        }

        const int *ft_arr = ft_vec.data();
        const int *std_arr = std_vec.data();

        for (int i = 0; i < 10; i++) {
            assert(ft_arr[i] == std_arr[i]);
        }
    }

    // --------------------------------------------------------
    // begin, end, rbegin, rend
    // --------------------------------------------------------
    // empty, size
    // --------------------------------------------------------
    // max_size
    {
        ft_vector ft_vec;
        ft_vec.max_size();
    }
    // --------------------------------------------------------
    // reserve
    // --------------------------------------------------------
    // capacity
    // --------------------------------------------------------
    // clear
    // --------------------------------------------------------
    // insert, erase
    // --------------------------------------------------------
    // push_back, pop_back
    {}
    // --------------------------------------------------------
    // resize
    // --------------------------------------------------------
    // swap
    // --------------------------------------------------------
    // operator==, !=, <, <=, >, >=

    OK();
}
