#include <iostream>

std::size_t nullNodeCounter = 0;

struct Node {
    Node* left;
    Node* right;
    int value;

    Node(const int value, Node* left = nullptr, Node* right = nullptr)
    : left{left}, right{right}, value{value} { }
};

void destroy(Node* node) {
    if(node->left) {
        destroy(node->left);
    }
    if(node->right) {
        destroy(node->right);
    }
    delete node;
}

Node* construct(const int* sortedArray, const std::size_t length) {
    if(length == 1) {
        return new Node{sortedArray[0]};
    }
    const std::size_t middle = length >> 1;
    const int middleValue = sortedArray[middle];
    Node* left = construct(sortedArray, middle);
    if((middle + 1) != length) {
        return new Node{middleValue, left, construct(sortedArray + middle + 1, length - middle - 1)};
    }
    return new Node{middleValue, left};
}

void print_null(const int value, std::ostream& out) {
    out << "    " << "null" << nullNodeCounter << " [shape=point];\n";
    out << "    " << value << " -> null" << nullNodeCounter << ";\n";
    ++nullNodeCounter;
}

void print(const Node* node, std::ostream& out) {
    if(!node->left && !node->right) return;
    if(node->left) {
        out << "    " << node->value << " -> " << node->left->value << ";\n";
        print(node->left, out);
    } else {
        print_null(node->value, out);
    }
    if(node->right) {
        out << "    " << node->value << " -> " << node->right->value << ";\n";
        print(node->right, out);
    } else {
        print_null(node->value, out);
    }
}

void print_in_dot(const Node* node, std::ostream& out) {
    out << "digraph BST {\n";
    if(node) {
        print(node, out);
    }
    out << '}' << std::endl;
}

int main() {
    const std::size_t length = (1 << 6) - 1;
    int sortedArray[length];
    for(unsigned int n = 0; n < length; ++n) {
        sortedArray[n] = n + 1;
    }
    Node* tree = construct(sortedArray, length);
    print_in_dot(tree, std::cout);
    destroy(tree);

    return 0;
}
