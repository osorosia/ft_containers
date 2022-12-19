#ifndef TEST_HPP
#define TEST_HPP

// #include "iterator_traits.hpp"
// #include "reverse_iterator.hpp"
// #include "vector.hpp"
#include "pair.hpp"

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

// using namespace std;

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
    { std::cout << YELLOW << "[" << name << "] " << END; }

#define TODO()                                                                                     \
    { std::cout << CYAN << "TODO " << END; }

#define OK()                                                                                       \
    { std::cout << GREEN << "OK" << END << std::endl; }

void pair_test();

#endif /* TEST_HPP */
