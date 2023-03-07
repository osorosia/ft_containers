#include "../_test.hpp"

void reverse_iterator_test() {
    TEST_NAME("reverse_iterator");

    typedef std::vector< int >                vector;
    typedef vector::iterator                  iterator;
    typedef std::reverse_iterator< iterator > std_reverse_iterator;
    typedef ft::reverse_iterator< iterator >  ft_reverse_iterator;

    {
        vector vec;
        for (int i = 0; i < 10; i++) {
            vec.push_back(i);
        }

        std_reverse_iterator std_begin = std_reverse_iterator(vec.end());
        std_reverse_iterator std_end   = std_reverse_iterator(vec.begin());
        ft_reverse_iterator  ft_begin  = ft_reverse_iterator(vec.end());
        ft_reverse_iterator  ft_end    = ft_reverse_iterator(vec.begin());

        assert(std::equal(std_begin, std_end, ft_begin));
        assert(std::equal(ft_begin, ft_end, std_begin));
    }

    OK();
}
