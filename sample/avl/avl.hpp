#ifndef AVL_HPP
#define AVL_HPP

#include <cstddef>

struct Node {
    Node* left;
    Node* right;
    long  val;

    Node(long val) : left(NULL), right(NULL), val(val) {}

    void insertNode(long num) {
        if (val == num)
            return;
        else if (num < val) {
            if (left == NULL)
                left = new Node(num);
            else
                left->insertNode(num);
        } else {
            if (right == NULL)
                right = new Node(num);
            else
                right->insertNode(num);
        }
    }

    Node *eraseNode(long num) {
        if (num == val) {
            if (!left)
                return right;
            if (!right)
                return left;
        }
        return NULL;
    }
};

struct AVLTree {
    Node* head;

    AVLTree() : head(NULL) {}

    void insert(long num) {
        if (!head) {
            head = new Node(num);
            return;
        }

        head->insertNode(num);
    }
    void erase(long num) {
        if (!head)
            return;
        head = head->eraseNode(num);
    }
};

#endif /* AVL_HPP */
