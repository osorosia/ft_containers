#include "avl.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

long calcDepth(Node* node) {
    if (node == NULL)
        return 0;
    long left  = calcDepth(node->left_);
    long right = calcDepth(node->right_);
    if (left < 0 || right < 0)
        return -1;

    long dh = abs(left - right);
    if (dh > 1)
        return -1;
    return max(left, right) + 1;
}

bool checkAVL(AVLTree& tree) { return calcDepth(tree.root_) >= 0; }
