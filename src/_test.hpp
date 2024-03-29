#ifndef TEST_HPP
#define TEST_HPP

#include "map.hpp"
#include "utils.hpp"
#include "vector.hpp"

// tree
#include "tree/avl_tree.h"

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

#define END            "\033[0m"
#define BOLD           "\033[1m"
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"
#define UNDERLINE      "\033[4m"
#define BOLD_UNDERLINE "\033[1;4m"

#define TEST_NAME(name)                                                                            \
    { std::cerr << YELLOW << std::setw(24) << name << ": " << END; }

#define TODO()                                                                                     \
    { std::cerr << CYAN << "TODO " << END; }

#define OK()                                                                                       \
    { std::cerr << GREEN << "OK" << END << std::endl; }

void vector_test();
void map_test();
// utils
void enable_if_test();
void equal_test();
void is_integral_test();
void iterator_traits_test();
void lexicographical_compare_test();
void pair_test();
void reverse_iterator_test();
// tree
void avl_tree_test();

#endif /* TEST_HPP */
