#include "avl.hpp"
#include "config.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

void checkAVL(Node* node) {
    if (node == NULL)
        return;
    checkAVL(node->left_);
    checkAVL(node->right_);

    long left  = node->left_ ? node->left_->height_ : 0;
    long right = node->right_ ? node->right_->height_ : 0;

    long dh = abs(left - right);
    assert(dh <= 1);
}

void checkHeight(Node* node) {
    if (node == NULL)
        return;
    checkHeight(node->left_);
    checkHeight(node->right_);
    long height
        = max(node->left_ ? node->left_->height_ : 0, node->right_ ? node->right_->height_ : 0) + 1;
    assert(height == node->height_);
}

void checkTree(AVLTree& tree, Node* node) {
    if (node == NULL)
        return;

    if (node == tree.root_) {
        assert(node->parent_ == NULL);
    }
    if (node->left_) {
        assert(node == node->left_->parent_);
    }
    if (node->right_) {
        assert(node == node->right_->parent_);
    }
    checkTree(tree, node->left_);
    checkTree(tree, node->right_);
}

void check(AVLTree& tree) {
    if (CHECK_AVL)
        checkAVL(tree.root_);
    if (CHECK_HEIGHT)
        checkHeight(tree.root_);
    checkTree(tree, tree.root_);
}
