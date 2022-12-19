#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template < class T1, class T2 >
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(), second() {}
    pair(const T1& t1, const T2& t2) : first(t1), second(t2) {}
    template < class U1, class U2 >
    pair(const pair< U1, U2 >& p) : first(p.first), second(p.second) {}

    pair& operator=(const pair& other) {
        this->first  = other.first;
        this->second = other.second;
        return *this;
    }
};

template < class T1, class T2 >
bool operator==(const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template < class T1, class T2 >
bool operator!=(const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs) {
    return !(lhs == rhs);
}

template < class T1, class T2 >
bool operator<(const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs) {
    return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template < class T1, class T2 >
bool operator<=(const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs) {
    return !(rhs < lhs);
}

template < class T1, class T2 >
bool operator>(const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs) {
    return rhs < lhs;
}

template < class T1, class T2 >
bool operator>=(const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs) {
    return !(lhs < rhs);
}

} // namespace ft

#endif /* PAIR_HPP */