#include <iostream>
#include "./Node.h"

Node* ExtractMaxNodeFromBST(Node* parent, Node* checked) {
    return checked->right
        ? ExtractMaxNodeFromBST(checked, checked->right)
        : (parent->right = checked->left, checked); 
}

Node* ReduceToBSTStep(Node* root) {
    if(!root->left && !root->right) {
        return root;
    }
    if(root->left && !root->right) {
        if(root->left->data < root->data) {
            return root;
        }
        Node* res = root->left;
        delete root;
        return res;
    }
    if(root->right && !root->left) {
        if(root->right->data >= root->data) {
            return root;
        }
        Node* res = root->right;
        delete root;
        return res;
    }
    if((root->left->data < root->data) && (root->right->data >= root->data)) {
        return root;
    }
    if(!root->left->right) {
        Node* res = root->left;
        res->right = root->right;
        delete root;
        return ReduceToBSTStep(res);
    }
    Node* max = ExtractMaxNodeFromBST(root, root->left);
    max->right = root->right;
    max->left = root->left;
    delete root;
    return ReduceToBSTStep(max);
}

Node* ReduceToBST(Node* root) {
    if(!root) {
        return nullptr;
    }
    if(root->left) {
        root->left = ReduceToBST(root->left);
    }
    if(root->right) {
        root->right = ReduceToBST(root->right);
    }
    return ReduceToBSTStep(root);
}

int main() {
    //Node* root = n(7, n(5, n(4), n(6)), n(9, n(8), n(10)));
    //Node* root = n(3, n(2, n(1), n(4)), n(5));
    //Node* root = n(3, n(2), n(4));
    //Node* root = n(5, n(20, n(30), n(10)), n(1));
    Node* root = n(5, n(7, n(8, n(3), n(5)), n(11, n(7), n(8))), n(9));
    root = ReduceToBST(root);
    std::cout << root->data << std::endl;
    DestroyTree(root);

    return 0;
}