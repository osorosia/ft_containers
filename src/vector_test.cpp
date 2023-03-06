#include "_test.hpp"

typedef ft::vector< int >  ft_vector;
typedef std::vector< int > std_vector;

typedef std::allocator< int > allocater_type;

#define vector_equal(ft_vec, std_vec)                                                              \
    {                                                                                              \
        assert(ft_vec.size() == std_vec.size());                                                   \
        for (int i = 0; i < ft_vec.size(); i++) {                                                  \
            assert(ft_vec[i] == std_vec[i]);                                                       \
        }                                                                                          \
    }

void vector_test() {
    TEST_NAME("vector");

    // --------------------------------------------------------
    // (constructor)
    { ft_vector ft_vec; }
    {
        allocater_type alloc = allocater_type();
        ft_vector      ft_vec(alloc);
    }
    {
        allocater_type alloc = allocater_type();

        ft_vector  ft_vec(10, 99, alloc);
        std_vector std_vec(10, 99, alloc);
        vector_equal(ft_vec, std_vec);
    }
    {
        ft_vector  ft_vec0;
        std_vector std_vec0;

        for (int i = 0; i < 10; i++) {
            ft_vec0.push_back(i);
            std_vec0.push_back(i);
        }

        ft_vector  ft_vec1(ft_vec0);
        std_vector std_vec1(std_vec0);
        vector_equal(ft_vec0, std_vec0);
        vector_equal(ft_vec1, std_vec1);
    }
    // --------------------------------------------------------
    // operator=
    {
        ft_vector  ft_vec0;
        std_vector std_vec0;
        ft_vector  ft_vec1;
        std_vector std_vec1;

        for (int i = 0; i < 10; i++) {
            ft_vec0.push_back(i);
            std_vec0.push_back(i);
        }

        ft_vec1  = ft_vec0;
        std_vec1 = std_vec0;
        vector_equal(ft_vec0, std_vec0);
        vector_equal(ft_vec1, std_vec1);
    }
    // --------------------------------------------------------
    // assign
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        ft_vec.assign((std::size_t)10, 1);
        std_vec.assign(10, 1);
        vector_equal(ft_vec, std_vec);
    }
    // --------------------------------------------------------
    // get_allocator
    {
        allocater_type alloc = allocater_type();
        ft_vector      ft_vec(alloc);
        assert(ft_vec.get_allocator() == alloc);
    }
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

        const int* ft_arr  = ft_vec.data();
        const int* std_arr = std_vec.data();

        for (int i = 0; i < 10; i++) {
            assert(ft_arr[i] == std_arr[i]);
        }
    }

    // --------------------------------------------------------
    // begin, end, rbegin, rend
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);

            // begin, rbegin
            assert(*(ft_vec.begin()) == *(std_vec.begin()));
            assert(*(ft_vec.rbegin()) == *(std_vec.rbegin()));

            // end, rend
            ft_vector::iterator          ft_end_it   = ft_vec.end();
            ft_vector::reverse_iterator  ft_rend_it  = ft_vec.rend();
            std_vector::iterator         std_end_it  = std_vec.end();
            std_vector::reverse_iterator std_rend_it = std_vec.rend();
            ft_end_it--;
            ft_rend_it--;
            std_end_it--;
            std_rend_it--;

            assert(*ft_end_it == *std_end_it);
            assert(*ft_rend_it == *std_rend_it);
        }
    }
    // --------------------------------------------------------
    // empty, size
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        assert(ft_vec.empty() == std_vec.empty());
        assert(ft_vec.size() == std_vec.size());

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);

            assert(ft_vec.empty() == std_vec.empty());
            assert(ft_vec.size() == std_vec.size());
        }
    }
    // --------------------------------------------------------
    // max_size
    {
        ft_vector ft_vec;
        ft_vec.max_size();
    }
    // --------------------------------------------------------
    // reserve, capacity
    {
        ft_vector ft_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            assert(ft_vec.capacity() >= i + 1);
        }

        ft_vector::size_type new_cap = ft_vec.capacity() * 2;
        ft_vec.reserve(new_cap);

        assert(ft_vec.capacity() >= new_cap);
    }
    // --------------------------------------------------------
    // clear
    {
        ft_vector ft_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
        }

        ft_vector::size_type cap = ft_vec.capacity();

        ft_vec.clear();
        assert(ft_vec.size() == 0);
        assert(ft_vec.capacity() == cap);
    }
    // --------------------------------------------------------
    // insert
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);
        }
        {
            ft_vector::iterator  ft_it  = ft_vec.insert(ft_vec.begin() + 2, 11);
            std_vector::iterator std_it = std_vec.insert(std_vec.begin() + 2, 11);
            vector_equal(ft_vec, std_vec);
            assert((ft_it - ft_vec.begin()) == (std_it - std_vec.begin()));
        }
        {
            ft_vec.insert(ft_vec.begin() + 2, 5, 22);
            std_vec.insert(std_vec.begin() + 2, 5, 22);
            vector_equal(ft_vec, std_vec);
        }
        {
            std_vector ft_v;
            std_vector std_v;
            for (int i = 0; i < 10; i++) {
                ft_v.push_back(i + 100);
                std_v.push_back(i + 100);
            }

            ft_vec.insert(ft_vec.begin() + 2, ft_v.begin(), ft_v.end());
            std_vec.insert(std_vec.begin() + 2, std_v.begin(), std_v.end());
            vector_equal(ft_vec, std_vec);
        }
    }
    // --------------------------------------------------------
    // erase
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);
        }
        {
            ft_vector::iterator  ft_it  = ft_vec.erase(ft_vec.begin() + 2);
            std_vector::iterator std_it = std_vec.erase(std_vec.begin() + 2);
            vector_equal(ft_vec, std_vec);
            assert((ft_it - ft_vec.begin()) == (std_it - std_vec.begin()));
        }
        {
            ft_vector::iterator  ft_it  = ft_vec.erase(ft_vec.begin() + 2, ft_vec.begin() + 5);
            std_vector::iterator std_it = std_vec.erase(std_vec.begin() + 2, std_vec.begin() + 5);
            vector_equal(ft_vec, std_vec);
            assert((ft_it - ft_vec.begin()) == (std_it - std_vec.begin()));
        }
        {
            ft_vector::iterator  ft_it  = ft_vec.erase(ft_vec.begin(), ft_vec.end());
            std_vector::iterator std_it = std_vec.erase(std_vec.begin(), std_vec.end());
            vector_equal(ft_vec, std_vec);
            assert((ft_it - ft_vec.begin()) == (std_it - std_vec.begin()));
        }
    }
    // --------------------------------------------------------
    // push_back, pop_back
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        for (int i = 0; i < 10; i++) {
            ft_vec.push_back(i);
            std_vec.push_back(i);

            vector_equal(ft_vec, std_vec);
        }

        for (int i = 0; i < 10; i++) {
            ft_vec.pop_back();
            std_vec.pop_back();

            vector_equal(ft_vec, std_vec);
        }
    }
    // --------------------------------------------------------
    // resize
    {
        ft_vector  ft_vec;
        std_vector std_vec;

        ft_vec.resize(3, 1);
        std_vec.resize(3, 1);

        vector_equal(ft_vec, std_vec);

        ft_vec.resize(10, 2);
        std_vec.resize(10, 2);

        vector_equal(ft_vec, std_vec);
    }

    // --------------------------------------------------------
    // swap
    {
        ft_vector  ft_vec0;
        ft_vector  ft_vec1;
        std_vector std_vec0;
        std_vector std_vec1;

        for (int i = 0; i < 10; i++) {
            ft_vec0.push_back(i);
            ft_vec1.push_back(i + 10);
            std_vec0.push_back(i);
            std_vec1.push_back(i + 10);
        }

        vector_equal(ft_vec0, std_vec0);
        vector_equal(ft_vec1, std_vec1);

        ft_vec0.swap(ft_vec1);
        std_vec0.swap(std_vec1);
        vector_equal(ft_vec0, std_vec0);
        vector_equal(ft_vec1, std_vec1);

        swap(ft_vec0, ft_vec1);
        swap(std_vec0, std_vec1);
        vector_equal(ft_vec0, std_vec0);
        vector_equal(ft_vec1, std_vec1);

        swap(ft_vec0, ft_vec0);
        swap(std_vec0, std_vec0);
        vector_equal(ft_vec0, std_vec0);
    }
    // --------------------------------------------------------
    // operator==, !=, <, <=, >, >=
    {
        for (int i0 = -1; i0 <= 1; i0++) {
            for (int j0 = -1; j0 <= 1; j0++) {
                for (int i1 = -1; i1 <= 1; i1++) {
                    for (int j1 = -1; j1 <= 1; j1++) {
                        ft_vector  ft_vec0;
                        ft_vector  ft_vec1;
                        std_vector std_vec0;
                        std_vector std_vec1;

                        ft_vec0.push_back(i0);
                        ft_vec0.push_back(j0);
                        ft_vec1.push_back(i1);

                        std_vec0.push_back(i0);
                        std_vec0.push_back(j0);
                        std_vec1.push_back(i1);

                        assert((ft_vec0 == ft_vec1) == (std_vec0 == std_vec1));
                        assert((ft_vec0 != ft_vec1) == (std_vec0 != std_vec1));
                        assert((ft_vec0 < ft_vec1) == (std_vec0 < std_vec1));
                        assert((ft_vec0 <= ft_vec1) == (std_vec0 <= std_vec1));
                        assert((ft_vec0 > ft_vec1) == (std_vec0 > std_vec1));
                        assert((ft_vec0 >= ft_vec1) == (std_vec0 >= std_vec1));

                        ft_vec1.push_back(j1);
                        std_vec1.push_back(j1);

                        assert((ft_vec0 == ft_vec1) == (std_vec0 == std_vec1));
                        assert((ft_vec0 != ft_vec1) == (std_vec0 != std_vec1));
                        assert((ft_vec0 < ft_vec1) == (std_vec0 < std_vec1));
                        assert((ft_vec0 <= ft_vec1) == (std_vec0 <= std_vec1));
                        assert((ft_vec0 > ft_vec1) == (std_vec0 > std_vec1));
                        assert((ft_vec0 >= ft_vec1) == (std_vec0 >= std_vec1));
                    }
                }
            }
        }
    }

    OK();
}
