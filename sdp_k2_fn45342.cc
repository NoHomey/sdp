#include <iostream>
#include <cstddef>
#include <cassert>
#include <queue>
 
using N = unsigned long int;
 
using BloomF = N(*)(const N);
 
using AccumF = N(*)(const N, const N);
 
struct Node {
    Node* left;
    Node* right;
    N value;
 
    Node(const N value, Node* left = nullptr, Node* right = nullptr) noexcept
        : left{left}, right{right}, value{value} { }
};
 
Node* readTree(std::istream& treeInput) {
    assert(treeInput.get() == '(');
    if (treeInput.peek() == ')') {
        treeInput.ignore();
        return nullptr;
    }
    N value = 0;
    treeInput >> value;
    Node* node = new Node{ value, readTree(treeInput), readTree(treeInput) };
    assert(treeInput.get() == ')');
    return node;
}
 
void destroyTree(Node* root) noexcept {
    if (root) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}
 
void bloomTree(Node* root, BloomF f) {
    if (root) {
        if (root->left || root->right) {
            bloomTree(root->left, f);
            bloomTree(root->right, f);
        }
        else {
            root->left = new Node{ f(root->value) };
            root->right = new Node{ f(root->value) };
        }
    }
}
 
N accumTree(Node* root, const N initial, AccumF f) noexcept {
    return root ? (f(f(f(initial, root->value), accumTree(root->left, initial, f)), accumTree(root->right, initial, f))) : initial;
}
 
N id(const N value) noexcept { return value; }
 
N sum(const N left, const N right) noexcept { return left + right; }
 
N sub(const N left, const N right) noexcept { return left - right;  }
 
N square(const N value) noexcept { return value * value; }
 
N mul(const N left, const N right) noexcept { return left * right; }
 
N div(const N left, const N right) noexcept { return left / right; }
 
N bloomDiffTree(Node* root, const N initial, BloomF bloom, AccumF accum, AccumF result) {
    const N accumT = accumTree(root, initial, accum);
    bloomTree(root, bloom);
    const N accumBloomedT = accumTree(root, initial, accum);
    return result(accumBloomedT, accumT);
}
 
std::size_t max(const std::size_t a, const std::size_t b) {
    return a < b ? b : a;
}
 
std::size_t treeDepth(const Node* root) noexcept {
    return root ? (1 + max(treeDepth(root->left), treeDepth(root->right))) : 0;
}
 
void pretyPrint(const Node* root, std::ostream& out) {
    const std::size_t depth = treeDepth(root);
    if (!depth) return;
    std::queue<const Node*> nodesAtLevel;
    nodesAtLevel.push(root);
    for (std::size_t level = 1; level <= depth; ++level) {
        const std::size_t tabsBefore = (1 << (depth - level)) - 1;
        const std::size_t tabsBetween = level != 1 ? ((1 << (depth - level + 1)) - 1) : 0;
        const std::size_t levelLength = level != 1 ? (1 << (level - 1)) : 1;
        for (std::size_t tabs = 0; tabs < tabsBefore; ++tabs) {
            out << ' ';
        }
        for (std::size_t counter = 1; counter <= levelLength; ++counter) {
            const Node* node = nodesAtLevel.front();
            nodesAtLevel.pop();
            if (node) {
                nodesAtLevel.push(node->left);
                nodesAtLevel.push(node->right);
                out << node->value;
            }
            else {
                nodesAtLevel.push(nullptr);
                nodesAtLevel.push(nullptr);
                out << ' ';
            }
            if (counter != levelLength) {
                for (std::size_t tabs = 0; tabs < tabsBetween; ++tabs) {
                    out << ' ';
                }
            }
        }
        for (std::size_t tabs = 0; tabs < tabsBefore; ++tabs) {
            out << ' ';
        }
        out << '\n';
    }
}
 
int main() {
 
    Node* root = readTree(std::cin);
 
    std::cout << bloomDiffTree(root, 0, id, sum, sub) << std::endl;
 
    //std::cout << bloomDiffTree(root, 1, square, mul, div) << std::endl;
 
    //std::cout << treeDepth(root) << std::endl;
 
    pretyPrint(root, std::cout);
 
    destroyTree(root);
 
    return 0;
}
