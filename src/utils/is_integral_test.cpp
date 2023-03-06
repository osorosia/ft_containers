#include "../_test.hpp"

void is_integral_test() {
    TEST_NAME("is_integral");
    assert(ft::is_integral< bool >::value);
    assert(ft::is_integral< char >::value);
    assert(ft::is_integral< wchar_t >::value);
    assert(ft::is_integral< short >::value);
    assert(ft::is_integral< int >::value);
    assert(ft::is_integral< long >::value);
    assert(ft::is_integral< long long >::value);

    assert(ft::is_integral< unsigned char >::value);
    assert(ft::is_integral< unsigned short >::value);
    assert(ft::is_integral< unsigned int >::value);
    assert(ft::is_integral< unsigned long >::value);
    assert(ft::is_integral< unsigned long long >::value);

    assert(ft::is_integral< signed char >::value);
    assert(ft::is_integral< signed short >::value);
    assert(ft::is_integral< signed int >::value);
    assert(ft::is_integral< signed long >::value);
    assert(ft::is_integral< signed long long >::value);

    assert(ft::is_integral< const bool >::value);
    assert(ft::is_integral< const char >::value);
    assert(ft::is_integral< const wchar_t >::value);
    assert(ft::is_integral< const short >::value);
    assert(ft::is_integral< const int >::value);
    assert(ft::is_integral< const long >::value);
    assert(ft::is_integral< const long long >::value);
    OK();
}
