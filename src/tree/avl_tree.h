#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../utils.hpp"
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>

// debug
#define DEBUG false
// check
#define CHECK        false
#define CHECK_HEIGHT true
#define CHECK_AVL    true
#define CHECK_SIZE   true
// print
#define PRINT_HEIGHT false

#if DEBUG
#define DEBUG_NODE(node)                                                                           \
    {                                                                                              \
        std::cout << std::setw(16) << __func__ << ": " << std::setw(2) << node->value_.first;      \
        std::cout << " ";                                                                          \
        if (node->left_)                                                                           \
            std::cout << std::setw(2) << node->left_->value_.first;                                \
        else                                                                                       \
            std::cout << "__";                                                                     \
        std::cout << " ";                                                                          \
        if (node->right_)                                                                          \
            std::cout << std::setw(2) << node->right_->value_.first;                               \
        else                                                                                       \
            std::cout << "__";                                                                     \
        std::cout << std::endl;                                                                    \
    }
#else
#define DEBUG_NODE(node)                                                                           \
    {}
#endif

namespace ft {

template < class T >
struct Node {
    typedef T                  value_type;
    typedef Node< value_type > node_type;

    node_type* left_;
    node_type* right_;
    node_type* parent_;
    value_type value_;
    int        height_;

    Node()
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , value_(value_type())
        , height_(1) {}

    Node(value_type value)
        : left_(NULL)
        , right_(NULL)
        , parent_(NULL)
        , value_(value)
        , height_(1) {}

    node_type* next() {
        if (right_)
            return right_->find_min();
        node_type* node = this;
        while (node->parent_) {
            if (node->is_left()) {
                return node->parent_;
            }
            node = node->parent_;
        }
        return node;
    }
    node_type* prev() {
        if (left_)
            return left_->find_max();
        node_type* node = this;
        while (node->parent_) {
            if (node->is_right()) {
                return node->parent_;
            }
            node = node->parent_;
        }
        return node;
    }
    node_type* find_min() { return left_ ? left_->find_min() : this; }
    node_type* find_max() { return right_ ? right_->find_max() : this; }
    bool       is_left() { return this == parent_->left_; }
    bool       is_right() { return this == parent_->right_; }
};

template < class T >
class tree_iterator {
public:
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef Node< value_type >              node_type;
    typedef tree_iterator< value_type >     self_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t                  difference_type;

    node_type* node_;

    tree_iterator(node_type* node)
        : node_(node) {}

    value_type& operator*() const { return node_->value_; }
    value_type* operator->() const { return &(node_->value_); }
    self_type&  operator++() {
        node_ = node_->next();
        return *this;
    }
    self_type operator++(int) {
        self_type tmp = *this;
        node_         = node_->next();
        return tmp;
    }
    self_type& operator--() {
        node_ = node_->prev();
        return *this;
    }
    self_type operator--(int) {
        self_type tmp = *this;
        node_         = node_->prev();
        return tmp;
    }
};

template < class T >
bool operator==(const tree_iterator< T >& lhs, const tree_iterator< T >& rhs) {
    return lhs.node_ == rhs.node_;
}
template < class T >
bool operator!=(const tree_iterator< T >& lhs, const tree_iterator< T >& rhs) {
    return !(lhs == rhs);
}

template < class T >
class const_tree_iterator {
public:
    typedef T                                 value_type;
    typedef const T*                          pointer;
    typedef const T&                          reference;
    typedef Node< value_type >                node_type;
    typedef const_tree_iterator< value_type > self_type;
    typedef std::bidirectional_iterator_tag   iterator_category;
    typedef std::ptrdiff_t                    difference_type;

    node_type* node_;

    const_tree_iterator(node_type* node)
        : node_(node) {}

    const value_type& operator*() const { return node_->value_; }
    const value_type* operator->() const { return &(node_->value_); }
    self_type&        operator++() {
        node_ = node_->next();
        return *this;
    }
    self_type operator++(int) {
        self_type tmp = *this;
        node_         = node_->next();
        return tmp;
    }
    self_type& operator--() {
        node_ = node_->prev();
        return *this;
    }
    self_type operator--(int) {
        self_type tmp = *this;
        node_         = node_->prev();
        return tmp;
    }
};

template < class T >
bool operator==(const const_tree_iterator< T >& lhs, const const_tree_iterator< T >& rhs) {
    return lhs.node_ == rhs.node_;
}
template < class T >
bool operator!=(const const_tree_iterator< T >& lhs, const const_tree_iterator< T >& rhs) {
    return !(lhs == rhs);
}

template < class Key,
           class T,
           class Compare   = std::less< Key >,
           class Allocator = std::allocator< ft::pair< const Key, T > > >
class AvlTree {
public:
    typedef Key                                    key_type;
    typedef T                                      mapped_type;
    typedef ft::pair< const Key, T >               value_type;
    typedef std::size_t                            size_type;
    typedef std::ptrdiff_t                         difference_type;
    typedef Compare                                key_compare;
    typedef Allocator                              allocator_type;
    typedef tree_iterator< value_type >            iterator;
    typedef const_tree_iterator< value_type >      const_iterator;
    typedef ft::reverse_iterator< iterator >       reverse_iterator;
    typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;

    typedef Node< value_type >                                      node_type;
    typedef typename Allocator::template rebind< node_type >::other node_allocator_type;

private:
    node_type*          root_;
    node_type*          begin_;
    node_type*          end_;
    size_type           size_;
    node_allocator_type node_alloc_;
    key_compare         comp_;

public:
    AvlTree()
        : root_(NULL)
        , begin_(NULL)
        , size_(0)
        , node_alloc_(node_allocator_type())
        , comp_(key_compare()) {
        end_ = allocate_end_node();
    }

    explicit AvlTree(const Compare& comp, const Allocator& alloc = Allocator())
        : root_(NULL)
        , begin_(NULL)
        , size_(0)
        , node_alloc_(alloc)
        , comp_(comp) {
        end_ = allocate_end_node();
    }

    template < class InputIt >
    AvlTree(InputIt          first,
            InputIt          last,
            const Compare&   comp  = Compare(),
            const Allocator& alloc = Allocator())
        : root_(NULL)
        , begin_(NULL)
        , size_(0)
        , node_alloc_(alloc)
        , comp_(comp) {
        end_ = allocate_end_node();
        insert(first, last);
    }

    AvlTree(const AvlTree& other)
        : root_(NULL)
        , begin_(NULL)
        , size_(0)
        , node_alloc_(node_allocator_type())
        , comp_(key_compare()) {
        end_  = allocate_end_node();
        *this = other;
    }

    ~AvlTree() {
        deallocate_tree(root_);
        deallocate_node(end_);
    }

    AvlTree& operator=(const AvlTree& other) {
        if (this == &other) {
            return *this;
        }
        deallocate_tree(root_);
        size_  = 0;
        root_  = NULL;
        begin_ = NULL;
        insert(other.begin(), other.end());
        return *this;
    }

    allocator_type get_allocator() const { return allocator_type(node_alloc_); }

    //
    // Iterators
    //
    iterator begin() {
        if (size_ == 0)
            return end();
        return iterator(begin_);
    }
    const_iterator begin() const {
        if (size_ == 0)
            return end();
        return const_iterator(begin_);
    }

    iterator       end() { return iterator(end_); }
    const_iterator end() const { return const_iterator(end_); }

    reverse_iterator       rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator       rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    //
    // Capacity
    //
    bool empty() const { return begin() == end(); }

    size_type size() const { return size_; }

    size_type max_size() const {
        return std::min< size_type >(node_alloc_.max_size(),
                                     std::numeric_limits< difference_type >::max());
    }

    //
    // Modifiers
    //
    void clear() {
        deallocate_tree(root_);
        update_root(NULL);
        size_  = 0;
        begin_ = NULL;
    }

    ft::pair< iterator, bool > insert(const value_type& value) { return insert_node(root_, value); }
    iterator                   insert(iterator pos, const value_type& value) {
        (void)pos;
        return insert(value).first;
    }
    template < class InputIt >
    void insert(InputIt first, InputIt last) {
        for (InputIt it = first; it != last; it++) {
            insert(root_, *it);
        }
    }

    iterator erase(iterator pos) {
        iterator next = pos;
        next++;
        erase(pos->first);
        return next;
    }
    iterator erase(iterator first, iterator last) {
        iterator it = first;
        while (it != last) {
            it = erase(it);
        }
        return last;
    }
    size_type erase(const Key& key) { return erase_node(root_, key); }

    void swap(AvlTree& other) {
        node_type*          root_tmp       = root_;
        node_type*          begin_tmp      = begin_;
        node_type*          end_tmp        = end_;
        size_type           size_tmp       = size_;
        node_allocator_type node_alloc_tmp = node_alloc_;
        key_compare         comp_tmp       = comp_;

        root_       = other.root_;
        begin_      = other.begin_;
        end_        = other.end_;
        size_       = other.size_;
        node_alloc_ = other.node_alloc_;
        comp_       = other.comp_;

        other.root_       = root_tmp;
        other.begin_      = begin_tmp;
        other.end_        = end_tmp;
        other.size_       = size_tmp;
        other.node_alloc_ = node_alloc_tmp;
        other.comp_       = comp_tmp;
    }

    //
    // Lookup
    //
    size_type count(const Key& key) const { return find(key) != end(); }

    iterator find(const Key& key) {
        node_type* node = find_node(root_, key);
        return node ? iterator(node) : end();
    }
    const_iterator find(const Key& key) const {
        node_type* node = find_node(root_, key);
        return node ? const_iterator(node) : end();
    }

    ft::pair< iterator, iterator > equal_range(const Key& key) {
        return ft::pair< iterator, iterator >(lower_bound(key), upper_bound(key));
    }
    ft::pair< const_iterator, const_iterator > equal_range(const Key& key) const {
        return ft::pair< const_iterator, const_iterator >(lower_bound(key), upper_bound(key));
    }

    iterator lower_bound(const Key& key) {
        node_type* node = lower_bound_node(root_, key);
        return node ? iterator(node) : end();
    }
    const_iterator lower_bound(const Key& key) const {
        node_type* node = lower_bound_node(root_, key);
        return node ? const_iterator(node) : end();
    }

    iterator upper_bound(const Key& key) {
        node_type* node = upper_bound_node(root_, key);
        return node ? iterator(node) : end();
    }
    const_iterator upper_bound(const Key& key) const {
        node_type* node = upper_bound_node(root_, key);
        return node ? const_iterator(node) : end();
    }

    //
    // Observers
    //
    key_compare key_comp() const { return comp_; }

private:
    node_type* allocate_node(const value_type& value) {
        node_type* node = node_alloc_.allocate(1);
        node_alloc_.construct(node, value);
        return node;
    }

    node_type* allocate_end_node() {
        node_type* node = node_alloc_.allocate(1);
        node_alloc_.construct(node, value_type());
        return node;
    }

    void deallocate_node(node_type* node) {
        if (node == NULL)
            return;
        node_alloc_.destroy(node);
        node_alloc_.deallocate(node, 1);
    }

    void deallocate_tree(node_type* node) {
        if (node == NULL)
            return;
        deallocate_tree(node->left_);
        deallocate_tree(node->right_);
        deallocate_node(node);
    }

    ft::pair< iterator, bool > insert_node(node_type* node, const value_type& value) {
        if (root_ == NULL) {
            update_root(allocate_node(value));
            size_++;
            update_begin();
            return ft::pair< iterator, bool >(iterator(root_), true);
        }

        if (comp_(value.first, get_key(node))) {
            if (node->left_) {
                return insert_node(node->left_, value);
            } else {
                node_type* new_node  = allocate_node(value);
                node->left_          = new_node;
                node->left_->parent_ = node;
                update_height_to_root(node);
                size_++;
                rebalance(node);
                update_begin();
                return ft::pair< iterator, bool >(iterator(new_node), true);
            }
        } else if (comp_(get_key(node), value.first)) {
            if (node->right_) {
                return insert_node(node->right_, value);
            } else {
                node_type* new_node   = allocate_node(value);
                node->right_          = new_node;
                node->right_->parent_ = node;
                update_height_to_root(node);
                size_++;
                rebalance(node);
                update_begin();
                return ft::pair< iterator, bool >(iterator(new_node), true);
            }
        } else {
            return ft::pair< iterator, bool >(iterator(node), false);
        }
    }

    size_type erase_node(node_type* node, const Key& key) {
        if (node == NULL)
            return 0;

        if (comp_(key, get_key(node))) {
            return erase_node(node->left_, key);
        } else if (comp_(get_key(node), key)) {
            return erase_node(node->right_, key);
        } else {
            if (node->left_ == NULL && node->right_ == NULL) {
                // none
                replace_parent(node, NULL);
                update_height_to_root(node->parent_);
                size_--;
                rebalance(node->parent_);
            } else if (node->left_ == NULL) {
                // a right child
                replace_parent(node, node->right_);
                update_height_to_root(node->parent_);
                size_--;
                rebalance(node->parent_);
            } else if (node->right_ == NULL) {
                // a left child
                replace_parent(node, node->left_);
                update_height_to_root(node->parent_);
                size_--;
                rebalance(node->parent_);
            } else {
                // both children
                node_type* min        = node->right_->find_min();
                node_type* min_parent = min != node->right_ ? min->parent_ : min;
                replace_parent(min, min->right_);
                replace_node(node, min);
                update_height_to_root(min_parent);
                size_--;
                rebalance(min_parent);
            }
            deallocate_node(node);
            update_begin();
            return 1;
        }
    }

    void rebalance(node_type* node) {
        if (node == NULL)
            return;
        // DEBUG_NODE(node);
        rotate(node);
        if (!is_root(node))
            rebalance(node->parent_);
    }

    long get_balance(node_type* node) {
        return (node->left_ ? node->left_->height_ : 0)
               - (node->right_ ? node->right_->height_ : 0);
    }

    void rotate(node_type* node) {
        int balance = get_balance(node);

        if (-1 <= balance && balance <= 1)
            return;
        DEBUG_NODE(node);

        if (balance > 1) {
            if (get_balance(node->left_) < 0)
                rotate_left(node->left_);
            rotate_right(node);
        } else {
            if (get_balance(node->right_) > 0)
                rotate_right(node->right_);
            rotate_left(node);
        }
    }

    void rotate_left(node_type* node) {
        DEBUG_NODE(node);

        node_type* x = node;
        node_type* y = node->right_;
        put_node_to_right(x, y->left_);
        replace_parent(x, y);
        put_node_to_left(y, x);

        update_height_to_root(x);
    }

    void rotate_right(node_type* node) {
        DEBUG_NODE(node);

        node_type* x = node->left_;
        node_type* y = node;
        put_node_to_left(y, x->right_);
        replace_parent(y, x);
        put_node_to_right(x, y);

        update_height_to_root(y);
    }

    void put_node_to_left(node_type* node, node_type* child) {
        node->left_ = child;
        if (child)
            child->parent_ = node;
    }

    void put_node_to_right(node_type* node, node_type* child) {
        node->right_ = child;
        if (child)
            child->parent_ = node;
    }

    node_type* lower_bound_node(node_type* node, const Key& key) {
        if (node == NULL)
            return NULL;

        if (get_key(node) == key) {
            return node;
        } else if (get_key(node) < key) {
            return has_right(node) ? lower_bound_node(node->right_, key) : NULL;
        } else {
            node_type* child = node->left_;
            if (child == NULL)
                return node;

            node_type* bottom = lower_bound_node(child, key);
            return bottom ? bottom : node;
        }
    }

    node_type* upper_bound_node(node_type* node, const Key& key) {
        if (node == NULL)
            return NULL;

        if (get_key(node) <= key) {
            return has_right(node) ? upper_bound_node(node->right_, key) : NULL;
        } else {
            node_type* child = node->left_;
            if (child == NULL)
                return node;

            node_type* bottom = upper_bound_node(child, key);
            return bottom ? bottom : node;
        }
    }

    void replace_node(node_type* node, node_type* next) {
        // parent
        next->parent_ = node->parent_;
        if (is_root(node)) {
            root_ = next;
        } else {
            if (is_left(node)) {
                next->parent_->left_ = next;
            } else {
                next->parent_->right_ = next;
            }
        }
        // left
        next->left_ = node->left_;
        if (next->left_) {
            next->left_->parent_ = next;
        }
        // right
        next->right_ = node->right_;
        if (next->right_) {
            next->right_->parent_ = next;
        }
        // height
        next->height_ = node->height_;
    }

    void replace_parent(node_type* node, node_type* next) {
        if (is_root(node)) {
            update_root(next);
            return;
        }

        if (is_left(node)) {
            node->parent_->left_ = next;
        } else {
            node->parent_->right_ = next;
        }
        if (next) {
            next->parent_ = node->parent_;
        }
    }

    int      get_height(node_type* node) const { return node ? node->height_ : 0; }
    key_type get_key(node_type* node) const { return node->value_.first; }
    bool     has_left(node_type* node) const { return node->left_ != NULL; }
    bool     has_right(node_type* node) const { return node->right_ != NULL; }
    bool     is_empty() const { return root_ == NULL; }
    bool     is_left(node_type* node) const { return node && node == node->parent_->left_; }
    bool     is_right(node_type* node) const { return node && node == node->parent_->right_; }
    bool     is_root(node_type* node) const { return node == root_; }
    void     update_begin() { begin_ = size_ > 0 ? find_min_node(root_) : NULL; }
    void     update_left(node_type* node, node_type* child) {
        node->left_ = child;
        if (child)
            child->parent_ = node;
    }
    void update_right(node_type* node, node_type* child) {
        node->right_ = child;
        if (child)
            child->parent_ = node;
    }
    void update_root(node_type* node) {
        root_       = node;
        end_->left_ = node;
        if (node) {
            node->parent_ = end_;
        }
    }
    void update_height_to_root(node_type* node) {
        if (node == NULL)
            return;
        update_height(node);
        if (!is_root(node))
            update_height_to_root(node->parent_);
    }
    void update_height(node_type* node) {
        if (node == NULL)
            return;
        node->height_ = std::max(get_height(node->left_), get_height(node->right_)) + 1;
    }

    node_type* find_node(node_type* node, const Key& key) const {
        if (node == NULL)
            return NULL;
        if (comp_(key, get_key(node))) {
            return find_node(node->left_, key);
        } else if (comp_(get_key(node), key)) {
            return find_node(node->right_, key);
        } else {
            return node;
        }
    }

    node_type* find_min_node(node_type* node) const {
        if (node->left_)
            return find_min_node(node->left_);
        return node;
    }

    node_type* find_max_node(node_type* node) const {
        if (node->right_)
            return find_max_node(node->right_);
        return node;
    }

    bool compare_key(node_type* lhs, node_type* rhs) { return comp_(get_key(lhs), get_key(rhs)); }

    void check() {
        if (!CHECK)
            return;

        check_tree(root_);
        if (CHECK_HEIGHT)
            check_height(root_);
        if (CHECK_AVL)
            check_avl(root_);
        if (CHECK_SIZE)
            check_size();
        check_begin_end();
    }

    void check_size() { assert(size_ == calc_size(root_)); }

    size_type calc_size(node_type* node) {
        if (node == NULL)
            return 0;
        size_type left  = calc_size(node->left_);
        size_type right = calc_size(node->right_);
        return left + right + 1;
    }

    void check_begin_end() {
        // TODO:
    }

    void check_tree(node_type* node) {
        if (node == NULL)
            return;

        if (node->left_) {
            assert(node == node->left_->parent_);
            assert(compare_key(node->left_, node));
        }
        if (node->right_) {
            assert(node == node->right_->parent_);
            assert(compare_key(node, node->right_));
        }

        check_tree(node->left_);
        check_tree(node->right_);
    }

    void check_height(node_type* node) {
        if (node == NULL)
            return;

        if (node->left_ == NULL && node->right_ == NULL) {
            assert(node->height_ == 1);
        } else if (node->left_ == NULL) {
            assert(node->height_ == node->right_->height_ + 1);
        } else if (node->right_ == NULL) {
            assert(node->height_ == node->left_->height_ + 1);
        } else {
            int left  = node->left_->height_;
            int right = node->right_->height_;
            assert(node->height_ == std::max(left, right) + 1);
        }

        check_height(node->left_);
        check_height(node->right_);
    }

    void check_avl(node_type* node) {
        if (node == NULL)
            return;

        int left  = node->left_ ? node->left_->height_ : 0;
        int right = node->right_ ? node->right_->height_ : 0;
        assert(std::abs(left - right) <= 1);

        check_avl(node->left_);
        check_avl(node->right_);
    }

    void print(std::string title = "") {
        if (title != "")
            std::cout << "# " << title << std::endl;
        std::cout << "```mermaid" << std::endl;
        std::cout << "graph TB" << std::endl;

        std::string name = "O";
        print_node_init(root_, name);
        print_tree(root_, name);

        std::cout << "```" << std::endl;
    }
    void print_tree(node_type* node, std::string name) {
        if (node == NULL)
            return;

        // left
        if (!node->left_ && node->right_)
            print_node_null(name, name + "A");
        print_node(node->left_, name, name + "A");
        print_tree(node->left_, name + "A");

        // right
        if (node->left_ && !node->right_)
            print_node_null(name, name + "B");
        print_node(node->right_, name, name + "B");
        print_tree(node->right_, name + "B");
    }
    void print_node(node_type* node, std::string prev_name, std::string name) {
        if (node == NULL)
            return;
        std::cout << prev_name << "-->" << name << "((" << node->value_.first;
        if (PRINT_HEIGHT)
            std::cout << ", " << node->height_;
        std::cout << "))" << std::endl;
    }
    void print_node_init(node_type* node, std::string name) {
        std::cout << name << "((";

        if (node) {
            std::cout << node->value_.first;
            if (PRINT_HEIGHT)
                std::cout << ", " << node->height_;
        } else {
            std::cout << ".";
        }

        std::cout << "))" << std::endl;
    }
    void print_node_null(std::string prev_name, std::string name) {
        std::cout << prev_name << "-->" << name << "((.))" << std::endl;
    }
};

template < class Key, class T, class Compare, class Alloc >
bool operator==(const ft::AvlTree< Key, T, Compare, Alloc >& lhs,
                const ft::AvlTree< Key, T, Compare, Alloc >& rhs) {
    return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template < class Key, class T, class Compare, class Alloc >
bool operator!=(const ft::AvlTree< Key, T, Compare, Alloc >& lhs,
                const ft::AvlTree< Key, T, Compare, Alloc >& rhs) {
    return !(lhs == rhs);
}
template < class Key, class T, class Compare, class Alloc >
bool operator<(const ft::AvlTree< Key, T, Compare, Alloc >& lhs,
               const ft::AvlTree< Key, T, Compare, Alloc >& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template < class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::AvlTree< Key, T, Compare, Alloc >& lhs,
                const ft::AvlTree< Key, T, Compare, Alloc >& rhs) {
    return !(rhs < lhs);
}
template < class Key, class T, class Compare, class Alloc >
bool operator>(const ft::AvlTree< Key, T, Compare, Alloc >& lhs,
               const ft::AvlTree< Key, T, Compare, Alloc >& rhs) {
    return rhs < lhs;
}
template < class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::AvlTree< Key, T, Compare, Alloc >& lhs,
                const ft::AvlTree< Key, T, Compare, Alloc >& rhs) {
    return !(lhs < rhs);
}

} // namespace ft

#endif /* AVL_TREE_H */
