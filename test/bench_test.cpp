#include <iostream>
#include <stdlib.h>

#ifndef FT
#include <map>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <vector.hpp>
#endif

#define COUNT 100000
#define SEED  1

#define CLOCK_START(str)                                                                           \
    std::cout << str << std::endl;                                                                 \
    clock_t clock_start = clock();

#define CLOCK_END()                                                                                \
    clock_t clock_end = clock();                                                                   \
    std::cout << clock_end - clock_start << std::endl;

typedef ft::vector< int >   vector_int;
typedef ft::map< int, int > map_int;

void vector_init(vector_int& vec) {
    for (int i = 0; i < COUNT; i++) {
        vec.push_back(i);
    }
}

void map_init(map_int& mp) {
    for (int i = 0; i < COUNT; i++) {
        mp[i] = i;
    }
}

void vector_bench() {
    srand(SEED);
    // --------------------------------------------------------
    // vector/operator=
    {
        vector_int vec;
        vector_init(vec);

        vector_int vec1;

        CLOCK_START("vector/operator=");
        vec1 = vec;
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/assign
    {
        vector_int vec;
        vector_init(vec);

        vector_int vec1;

        CLOCK_START("vector/assign");
        vec1.assign(vec.begin(), vec.end());
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/get_allocator
    {
        vector_int vec;
        vector_init(vec);

        CLOCK_START("vector/get_allocator");
        for (int i = 0; i < COUNT; i++) {
            vec.get_allocator();
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/at, operator[], front, back, data
    {
        vector_int vec;
        vector_init(vec);
        {
            CLOCK_START("vector/at");
            for (int i = 0; i < COUNT; i++) {
                vec.at(i);
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/operator[]");
            for (int i = 0; i < COUNT; i++) {
                vec[i];
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/front");
            for (int i = 0; i < COUNT; i++) {
                vec.front();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/back");
            for (int i = 0; i < COUNT; i++) {
                vec.back();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/data");
            for (int i = 0; i < COUNT; i++) {
                vec.data();
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // vector/begin, end, rbegin, rend
    {
        vector_int vec;
        vector_init(vec);
        {
            CLOCK_START("vector/begin");
            for (int i = 0; i < COUNT; i++) {
                vec.begin();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/end");
            for (int i = 0; i < COUNT; i++) {
                vec.end();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/rbegin");
            for (int i = 0; i < COUNT; i++) {
                vec.rbegin();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/rend");
            for (int i = 0; i < COUNT; i++) {
                vec.rend();
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // vector/empty, size, max_size
    {
        vector_int vec;
        vector_init(vec);
        {
            CLOCK_START("vector/empty");
            for (int i = 0; i < COUNT; i++) {
                vec.empty();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/size");
            for (int i = 0; i < COUNT; i++) {
                vec.size();
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/max_size");
            for (int i = 0; i < COUNT; i++) {
                vec.max_size();
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // vector/reserve
    {
        vector_int vec;

        CLOCK_START("vector/reserve");
        for (int i = 0; i < COUNT; i++) {
            vec.reserve(COUNT);
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/capacity
    {
        vector_int vec;
        vector_init(vec);

        CLOCK_START("vector/capacity");
        for (int i = 0; i < COUNT; i++) {
            vec.capacity();
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/clear
    {
        vector_int vec;
        vector_init(vec);

        CLOCK_START("vector/clear");
        vec.clear();
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/insert
    {
        vector_int vec0;
        vector_int vec1;
        vector_init(vec0);
        vector_init(vec1);

        CLOCK_START("vector/insert");
        vec1.insert(vec1.begin(), vec0.begin(), vec0.end());
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/erase
    {
        vector_int vec;
        vector_init(vec);

        CLOCK_START("vector/erase");
        vec.erase(vec.begin(), vec.end());
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/push_back, pop_back
    {
        vector_int vec;
        {
            CLOCK_START("vector/push_back");
            for (int i = 0; i < COUNT; i++) {
                vec.push_back(i);
            }
            CLOCK_END();
        }
        {
            CLOCK_START("vector/pop_back");
            for (int i = 0; i < COUNT; i++) {
                vec.pop_back();
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // vector/resize
    {
        vector_int vec;

        CLOCK_START("vector/resize");
        vec.resize(COUNT);
        vec.resize(0);
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/swap
    {
        vector_int vec0;
        vector_int vec1;
        vector_init(vec0);
        vector_init(vec1);

        CLOCK_START("vector/swap");
        ft::swap(vec0, vec1);
        vec1.swap(vec0);
        CLOCK_END();
    }
    // --------------------------------------------------------
    // vector/operator==, !=, <, <=, >, >=
    {
        vector_int vec0;
        vector_int vec1;
        vector_init(vec0);
        vector_init(vec1);

        bool b;
        CLOCK_START("vector/operator==, etc");
        b = vec0 == vec1;
        b = vec0 != vec1;
        b = vec0 < vec1;
        b = vec0 <= vec1;
        b = vec0 > vec1;
        b = vec0 >= vec1;
        CLOCK_END();
        (void)b;
    }
}

void map_bench() {
    srand(SEED);
    // --------------------------------------------------------
    // map/operator=
    {
        map_int mp;
        map_init(mp);

        map_int mp1;

        CLOCK_START("map/operator=");
        mp1 = mp;
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/get_allocater
    {
        map_int mp;
        map_init(mp);

        CLOCK_START("map/get_allocater");
        for (int i = 0; i < COUNT; i++) {
            map_int::allocator_type alloc = mp.get_allocator();
            (void)alloc;
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/at
    {
        map_int mp;
        map_init(mp);

        long sum = 0;

        CLOCK_START("map/at");
        {
            for (int i = 0; i < COUNT; i++) {
                int num = rand() % COUNT;
                sum += mp.at(num);
            }
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/operator[]
    {
        CLOCK_START("map/operator[]");
        {
            map_int mp;
            for (int i = 0; i < COUNT; i++) {
                mp[i] = i;
            }
        }
        {
            map_int mp;
            for (int i = 0; i < COUNT; i++) {
                int num = rand();
                mp[num] = num;
            }
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/begin, end, rbegin, rend
    {
        map_int mp;
        map_init(mp);

        {
            CLOCK_START("map/begin");
            {
                for (int i = 0; i < COUNT; i++) {
                    map_int::iterator it = mp.begin();
                    (void)it;
                }
            }
            CLOCK_END();
        }

        {
            CLOCK_START("map/end");
            {
                for (int i = 0; i < COUNT; i++) {
                    map_int::iterator it = mp.end();
                    (void)it;
                }
            }
            CLOCK_END();
        }

        {
            CLOCK_START("map/rbegin");
            {
                for (int i = 0; i < COUNT; i++) {
                    map_int::reverse_iterator it = mp.rbegin();
                    (void)it;
                }
            }
            CLOCK_END();
        }

        {
            CLOCK_START("map/rend");
            {
                for (int i = 0; i < COUNT; i++) {
                    map_int::reverse_iterator it = mp.rend();
                    (void)it;
                }
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // map/empty, size, max_size
    {
        map_int mp;
        map_init(mp);

        {
            CLOCK_START("map/empty");
            for (int i = 0; i < COUNT; i++) {
                bool n = mp.empty();
                (void)n;
            }
            CLOCK_END();
        }
        {
            CLOCK_START("map/size");
            for (int i = 0; i < COUNT; i++) {
                std::size_t sz = mp.size();
                (void)sz;
            }
            CLOCK_END();
        }
        {
            CLOCK_START("map/max_size");
            for (int i = 0; i < COUNT; i++) {
                std::size_t sz = mp.max_size();
                (void)sz;
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // map/clear
    {
        map_int mp;
        map_init(mp);

        CLOCK_START("map/clear");
        mp.clear();
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/insert
    {
        map_int mp;

        CLOCK_START("map/insert");
        for (int i = 0; i < COUNT; i++) {
            int num = rand();
            mp.insert(ft::make_pair(num, num));
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/erase
    {
        map_int mp;
        map_init(mp);

        CLOCK_START("map/erase");
        for (int i = 0; i < COUNT; i++) {
            mp.erase(rand() % COUNT);
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/swap
    {
        map_int mp0;
        map_int mp1;
        map_init(mp0);
        map_init(mp1);

        CLOCK_START("map/swap");
        ft::swap(mp0, mp1);
        mp0.swap(mp1);
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/count
    {
        map_int mp;
        map_init(mp);

        CLOCK_START("map/count");
        for (int i = 0; i < COUNT; i++) {
            mp.count(i);
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/find
    {
        map_int mp;
        map_init(mp);

        CLOCK_START("map/find");
        for (int i = 0; i < COUNT; i++) {
            mp.find(i);
        }
        CLOCK_END();
    }
    // --------------------------------------------------------
    // map/equal_range, lower_bound, upper_bound
    {
        map_int mp;
        map_init(mp);

        {
            CLOCK_START("map/equal_range");
            for (int i = 0; i < COUNT; i++) {
                mp.equal_range(i);
            }
            CLOCK_END();
        }
        {
            CLOCK_START("map/lower_bound");
            for (int i = 0; i < COUNT; i++) {
                mp.lower_bound(i);
            }
            CLOCK_END();
        }
        {
            CLOCK_START("map/upper_bound");
            for (int i = 0; i < COUNT; i++) {
                mp.upper_bound(i);
            }
            CLOCK_END();
        }
    }
    // --------------------------------------------------------
    // map/operator==, !=, <, <=, >, >=
    {
        map_int mp0;
        map_int mp1;
        map_init(mp0);
        map_init(mp1);

        bool b;
        CLOCK_START("map/operator==, etc");
        b = mp0 == mp1;
        b = mp0 != mp1;
        b = mp0 < mp1;
        b = mp0 <= mp1;
        b = mp0 > mp1;
        b = mp0 >= mp1;
        CLOCK_END();
        (void)b;
    }
}

int main() {
    vector_bench();
    map_bench();
}
