#include "test.h"

void vector_at() {
    CASE_NAME("vector_at");

    vector< int > vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    OK(1, vec.at(0));
    OK(2, vec.at(1));
    OK(3, vec.at(2));

    try {
        vec.at(-1);
        RESULT(false);
    } catch (std::exception &e) {
        RESULT(true);
    }

    try {
        vec.at(vec.size());
        RESULT(false);
    } catch (std::exception &e) {
        RESULT(true);
    }
}

void vector_front() {
}

void vector_back() {
}

void vector_test() {
    TEST_NAME("vector_test");

    vector_at();
    vector_front();
    vector_back();

    TEST_END();
}
