#pragma once

struct Node {
    Node* left;
    Node* right;
    int data;

    Node(int data, Node* left, Node* right)
    : left{left}, right{right}, data{data} { }
};

Node* n(int data, Node* left = nullptr, Node* right = nullptr);

void DestroyTree(Node* root);