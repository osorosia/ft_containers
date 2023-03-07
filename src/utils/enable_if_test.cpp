#include "../_test.hpp"

void enable_if_test() {
    TEST_NAME("enable_if");

    {
        // ok
        ft::enable_if< true, int >::type a;
        (void)a;
    }
    {
        // ng
        // ft::enable_if< false, int >::type a;
        // (void)a;
    }

    OK();
}
