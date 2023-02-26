#include "avl.hpp"
#include "config.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

long calcAndCheckHeight(Node* node) {
    if (node == NULL)
        return 0;
    assert(!node->left_ || node == node->left_->parent_);
    assert(!node->right_ || node == node->right_->parent_);

    long left  = calcAndCheckHeight(node->left_);
    long right = calcAndCheckHeight(node->right_);
    if (left < 0 || right < 0)
        return -1;

    long dh = abs(left - right);
    if (dh > 1)
        return -1;
    return max(left, right) + 1;
}

bool checkAVL(AVLTree& tree) { return calcAndCheckHeight(tree.root_) >= 0; }
