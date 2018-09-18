#include <iostream>
#include "./Queue.hpp"
#include "./Node.h"

bool IsFull(const Node* root) {
    if(!root) {
        return true;
    }
    std::size_t prevLevelCount = 1;
    Queue<const Node*> level{2};
    level.enqueue(root);
    while(!level.isEmpty()) {
        std::size_t levelCount = 0;
        for(std::size_t count = 0; count < prevLevelCount; ++count) {
            const Node* node = level.dequeue();
            if(node->left) {
                ++levelCount;
                level.enqueue(node->left);
            }
            if(node->right) {
                ++levelCount;
                level.enqueue(node->right);
            }
        }
        if(levelCount == 0) {
            return true;
        }
        if(levelCount != (2 * prevLevelCount)) {
            return false;
        }
        prevLevelCount = levelCount;
    }
    return true;
}

int main() {
    Node* root = n(7, n(5, n(4), n(6)), n(9, n(8), n(10)));
    std::cout << (IsFull(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(3, n(2, n(1), n(4)), n(5));
    std::cout << (IsFull(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(3, n(2), n(4));
    std::cout << (IsFull(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(5);
    std::cout << (IsFull(root) == true)  << std::endl;
    DestroyTree(root);

    root = nullptr;
    std::cout << (IsFull(root) == true)  << std::endl;
    DestroyTree(root);

    root = n(1, nullptr, n(3));
    std::cout << (IsFull(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(1, n(2), nullptr);
    std::cout << (IsFull(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(5, n(2), n(5)));
    std::cout << (IsFull(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(7, n(6), n(6)));
    std::cout << (IsFull(root) == false)  << std::endl;
    DestroyTree(root);

    root = n(5, nullptr, n(7, n(6), n(7)));
    std::cout << (IsFull(root) == false)  << std::endl;
    DestroyTree(root);

    return 0;
}