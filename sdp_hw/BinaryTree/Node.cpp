#include "./Node.h"

Node* n(int data, Node* left, Node* right) {
    return new Node{data, left, right};
}

void DestroyTree(Node* root) {
    if(root) {
        DestroyTree(root->left);
        DestroyTree(root->right);
        delete root;
    }
}