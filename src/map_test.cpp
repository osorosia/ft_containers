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

static void map_equal(ft_map& ft_mp, std_map& std_mp) {
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
    {
        ft_map  ft_mp;
        std_map std_mp;

        assert((ft_mp.begin() == ft_mp.end()) == (std_mp.begin() == std_mp.end()));
        assert((ft_mp.rbegin() == ft_mp.rend()) == (std_mp.rbegin() == std_mp.rend()));
        for (int i = 0; i < 10; i++) {
            map_insert_helper(ft_mp, std_mp, i, i);

            assert(ft_mp.begin()->first == std_mp.begin()->first);
            assert(ft_mp.rbegin()->first == std_mp.rbegin()->first);

            ft_map::iterator          ft_end_it   = ft_mp.end();
            std_map::iterator         std_end_it  = std_mp.end();
            ft_map::reverse_iterator  ft_rend_it  = ft_mp.rend();
            std_map::reverse_iterator std_rend_it = std_mp.rend();
            ft_end_it--;
            std_end_it--;
            ft_rend_it--;
            std_rend_it--;

            assert(ft_end_it->first == std_end_it->first);
            assert(ft_rend_it->first == std_rend_it->first);
            assert((ft_mp.begin() == ft_mp.end()) == (std_mp.begin() == std_mp.end()));
            assert((ft_mp.rbegin() == ft_mp.rend()) == (std_mp.rbegin() == std_mp.rend()));
        }
    }
    {
        ft_map  ft_mp;
        std_map std_mp;

        for (int i = 10; i > 0; i--) {
            map_insert_helper(ft_mp, std_mp, i, i);

            assert(ft_mp.begin()->first == std_mp.begin()->first);
            assert(ft_mp.rbegin()->first == std_mp.rbegin()->first);

            ft_map::iterator          ft_end_it   = ft_mp.end();
            std_map::iterator         std_end_it  = std_mp.end();
            ft_map::reverse_iterator  ft_rend_it  = ft_mp.rend();
            std_map::reverse_iterator std_rend_it = std_mp.rend();
            ft_end_it--;
            std_end_it--;
            ft_rend_it--;
            std_rend_it--;

            assert(ft_end_it->first == std_end_it->first);
            assert(ft_rend_it->first == std_rend_it->first);
            assert((ft_mp.begin() == ft_mp.end()) == (std_mp.begin() == std_mp.end()));
            assert((ft_mp.rbegin() == ft_mp.rend()) == (std_mp.rbegin() == std_mp.rend()));
        }
    }

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
    // TODO:

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
            map_equal(ft_mp, std_mp);
        }
    }

    // --------------------------------------------------------
    // swap
    {
        ft_map  ft_mp0;
        ft_map  ft_mp1;
        std_map std_mp0;
        std_map std_mp1;

        for (int i = 0; i < 10; i++) {
            map_insert_helper(ft_mp0, std_mp0, i, i);
            map_insert_helper(ft_mp1, std_mp1, i + 10, i + 10);
        }
        ft_mp0.swap(ft_mp1);
        std_mp0.swap(std_mp1);
        map_equal(ft_mp0, std_mp0);
        map_equal(ft_mp1, std_mp1);

        ft::swap(ft_mp0, ft_mp1);
        std::swap(std_mp0, std_mp1);
        map_equal(ft_mp0, std_mp0);
        map_equal(ft_mp1, std_mp1);
    }

    // --------------------------------------------------------
    // count, find
    {
        ft_map  ft_mp;
        std_map std_mp;

        for (int i = 0; i < 10; i++) {
            assert(ft_mp.count(i) == std_mp.count(i));
            assert(ft_mp.find(i) == ft_mp.end());
            assert(std_mp.find(i) == std_mp.end());

            map_insert_helper(ft_mp, std_mp, i, i);

            assert(ft_mp.count(i) == std_mp.count(i));
            assert(ft_mp.find(i)->first == std_mp.find(i)->first);
        }
    }

    // --------------------------------------------------------
    // equal_range, lower_bound, upper_bound
    {
        ft_map  ft_mp;
        std_map std_mp;

        for (int i = 0; i < 10; i++) {
            map_insert_helper(ft_mp, std_mp, i, i);
        }

        {
            int key = -1;

            ft_map::iterator ft_low_it = ft_mp.lower_bound(key);
            ft_map::iterator ft_up_it  = ft_mp.upper_bound(key);
            ft_map::iterator ft_eq1_it = ft_mp.equal_range(key).first;
            ft_map::iterator ft_eq2_it = ft_mp.equal_range(key).second;

            std_map::iterator std_low_it = std_mp.lower_bound(key);
            std_map::iterator std_up_it  = std_mp.upper_bound(key);
            std_map::iterator std_eq1_it = std_mp.equal_range(key).first;
            std_map::iterator std_eq2_it = std_mp.equal_range(key).second;

            assert((ft_low_it == ft_mp.end()) == (std_low_it == std_mp.end()));
            assert((ft_up_it == ft_mp.end()) == (std_up_it == std_mp.end()));
            assert((ft_low_it == ft_eq1_it) == (std_low_it == std_eq1_it));
            assert((ft_up_it == ft_eq2_it) == (std_up_it == std_eq2_it));

            assert(ft_low_it->first == std_low_it->first);
            assert(ft_up_it->first == std_up_it->first);
        }
        {
            int key = 0;

            ft_map::iterator ft_low_it = ft_mp.lower_bound(key);
            ft_map::iterator ft_up_it  = ft_mp.upper_bound(key);
            ft_map::iterator ft_eq1_it = ft_mp.equal_range(key).first;
            ft_map::iterator ft_eq2_it = ft_mp.equal_range(key).second;

            std_map::iterator std_low_it = std_mp.lower_bound(key);
            std_map::iterator std_up_it  = std_mp.upper_bound(key);
            std_map::iterator std_eq1_it = std_mp.equal_range(key).first;
            std_map::iterator std_eq2_it = std_mp.equal_range(key).second;

            assert((ft_low_it == ft_mp.end()) == (std_low_it == std_mp.end()));
            assert((ft_up_it == ft_mp.end()) == (std_up_it == std_mp.end()));
            assert((ft_low_it == ft_eq1_it) == (std_low_it == std_eq1_it));
            assert((ft_up_it == ft_eq2_it) == (std_up_it == std_eq2_it));

            assert(ft_low_it->first == std_low_it->first);
            assert(ft_up_it->first == std_up_it->first);
        }
        {
            int key = 9;

            ft_map::iterator ft_low_it = ft_mp.lower_bound(key);
            ft_map::iterator ft_up_it  = ft_mp.upper_bound(key);
            ft_map::iterator ft_eq1_it = ft_mp.equal_range(key).first;
            ft_map::iterator ft_eq2_it = ft_mp.equal_range(key).second;

            std_map::iterator std_low_it = std_mp.lower_bound(key);
            std_map::iterator std_up_it  = std_mp.upper_bound(key);
            std_map::iterator std_eq1_it = std_mp.equal_range(key).first;
            std_map::iterator std_eq2_it = std_mp.equal_range(key).second;

            assert((ft_low_it == ft_mp.end()) == (std_low_it == std_mp.end()));
            assert((ft_up_it == ft_mp.end()) == (std_up_it == std_mp.end()));
            assert((ft_low_it == ft_eq1_it) == (std_low_it == std_eq1_it));
            assert((ft_up_it == ft_eq2_it) == (std_up_it == std_eq2_it));

            assert(ft_low_it->first == std_low_it->first);
            // assert(ft_up_it->first == std_up_it->first);
        }
        {
            int key = 10;

            ft_map::iterator ft_low_it = ft_mp.lower_bound(key);
            ft_map::iterator ft_up_it  = ft_mp.upper_bound(key);
            ft_map::iterator ft_eq1_it = ft_mp.equal_range(key).first;
            ft_map::iterator ft_eq2_it = ft_mp.equal_range(key).second;

            std_map::iterator std_low_it = std_mp.lower_bound(key);
            std_map::iterator std_up_it  = std_mp.upper_bound(key);
            std_map::iterator std_eq1_it = std_mp.equal_range(key).first;
            std_map::iterator std_eq2_it = std_mp.equal_range(key).second;

            assert((ft_low_it == ft_mp.end()) == (std_low_it == std_mp.end()));
            assert((ft_up_it == ft_mp.end()) == (std_up_it == std_mp.end()));
            assert((ft_low_it == ft_eq1_it) == (std_low_it == std_eq1_it));
            assert((ft_up_it == ft_eq2_it) == (std_up_it == std_eq2_it));

            // assert(ft_low_it->first == std_low_it->first);
            // assert(ft_up_it->first == std_up_it->first);
        }
    }

    // --------------------------------------------------------
    // key_comp, value_comp
    // --------------------------------------------------------
    // operator==, !=, <, <=, >, >=

    OK();
}
