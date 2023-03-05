#include "_test.hpp"

typedef ft::map< int, int >   ft_map;
typedef std::map< int, int >  std_map;
typedef ft::pair< int, int >  ft_value_type;
typedef std::pair< int, int > std_value_type;

static void map_insert_helper(ft_map& ft_mp, std_map& std_mp, int key, int val) {
    ft_mp.insert(ft_value_type(key, val));
    std_mp.insert(std_value_type(key, val));
}

static void map_erase_helper(ft_map& ft_mp, std_map& std_mp, int key) {
    ft_mp.erase(key);
    std_mp.erase(key);
}

static void equal_map(ft_map& ft_mp, std_map& std_mp) {
    assert(ft_mp.size() == std_mp.size());

    ft_map::iterator  ft_it  = ft_mp.begin();
    std_map::iterator std_it = std_mp.begin();
    for (; ft_it != ft_mp.end() && std_it != std_mp.end(); ft_it++, std_it++) {
        assert(ft_it->first == std_it->first);
        assert(ft_it->second == std_it->second);
    }
    assert(ft_it == ft_mp.end());
    assert(std_it == std_mp.end());
}

void map_test() {
    TEST_NAME("map");

    // --------------------------------------------------------
    // operator=
    // --------------------------------------------------------
    // get_allocator
    // --------------------------------------------------------
    // at, operator[]
    // --------------------------------------------------------
    // begin, end, rbegin, rend
    // --------------------------------------------------------
    // empty, size
    {
        ft_map  ft_mp;
        std_map std_mp;

        assert(ft_mp.empty() == std_mp.empty());

        map_insert_helper(ft_mp, std_mp, 1, 0);
        assert(ft_mp.empty() == std_mp.empty());
        assert(ft_mp.size() == std_mp.size());

        map_insert_helper(ft_mp, std_mp, 2, 0);
        assert(ft_mp.empty() == std_mp.empty());
        assert(ft_mp.size() == std_mp.size());

        map_erase_helper(ft_mp, std_mp, 1);
        assert(ft_mp.empty() == std_mp.empty());
        assert(ft_mp.size() == std_mp.size());

        map_erase_helper(ft_mp, std_mp, 2);
        assert(ft_mp.empty() == std_mp.empty());
        assert(ft_mp.size() == std_mp.size());
    }

    // --------------------------------------------------------
    // max_size

    // --------------------------------------------------------
    // clear
    {
        ft_map ft_mp;

        for (int i = 1; i < 10; i++) {
            ft_mp[i] = i;
            assert(ft_mp.size() == i);
        }
        ft_mp.clear();
        assert(ft_mp.size() == 0);
        assert(ft_mp.begin() == ft_mp.end());

        for (int i = 1; i < 10; i++) {
            ft_mp[i] = i;
            assert(ft_mp.size() == i);
        }
        ft_mp.clear();
        assert(ft_mp.size() == 0);
        assert(ft_mp.begin() == ft_mp.end());
    }

    // --------------------------------------------------------
    // insert, erase
    {
        ft_map  ft_mp;
        std_map std_mp;

        struct {
            std::string op;
            int         val;
        } cases[] = {
            {"insert", 10}, {"insert", 1},  {"insert", 2},  {"insert", 0},  {"insert", 15},
            {"insert", 12}, {"insert", 11}, {"insert", 13}, {"insert", 20}, {"insert", 18},
            {"erase", 15},  {"erase", 13},  {"erase", 12},  {"erase", 10},  {"erase", 11},
            {"erase", 1},   {"erase", 21},  {"erase", 20},  {"erase", 18},  {"erase", 0},
            {"erase", 2},
        };

        for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
            if (cases[i].op == "insert") {
                map_insert_helper(ft_mp, std_mp, cases[i].val, cases[i].val);
            } else if (cases[i].op == "erase") {
                map_erase_helper(ft_mp, std_mp, cases[i].val);
            }
            equal_map(ft_mp, std_mp);
        }
    }
    // --------------------------------------------------------
    // swap
    // --------------------------------------------------------
    // count, find
    // --------------------------------------------------------
    // equal_range, lower_bound, upper_bound
    // --------------------------------------------------------
    // key_comp, value_comp
    // --------------------------------------------------------
    // operator==, !=, <, <=, >, >=

    OK();
}
