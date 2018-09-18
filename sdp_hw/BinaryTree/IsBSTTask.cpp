#include <iostream>
#include <limits>
#include "./Node.h"

bool IsBstUtil(const Node* root, int leftLimit, int rightLimit) {
    if(!root) {
        return true;
    }
    const int data = root->data;
    if((data < leftLimit) || (data > rightLimit)) {
        return false;
    }
    return IsBstUtil(root->left, leftLimit, data - 1) && IsBstUtil(root->right, data, rightLimit);
}

bool IsBst(const Node* root) {
    return IsBstUtil(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main() {
    Node* root = n(7, n(5, n(4), n(6)), n(9, n(8), n(10)));
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(3, n(2, n(1), n(4)), n(5));
    std::cout << (IsBst(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(3, n(2), n(4));
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(5);
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(5, n(2), n(5));
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(5, n(2, n(5), n(4)), n(5));
    std::cout << (IsBst(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(5));
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(5, n(2), nullptr);
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(5, n(2), n(5)));
    std::cout << (IsBst(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(7, n(6), n(6)));
    std::cout << (IsBst(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(7, n(6), n(7)));
    std::cout << (IsBst(root) == true)  << std::endl;
    DestroyTree(root);

    root = nullptr;
    std::cout << (IsBst(root) == true)  << std::endl;

    return 0;
}