#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int data, Node* next): data{data}, next{next} { }
};

void Rearrange(Node*& head) {
    Node* evensHead = nullptr;
    Node* oddsHead = nullptr;
    Node* evensTail = nullptr;
    Node* oddsTail = nullptr;
    Node* it = head;

    while(it) {
        const bool isOdd = it->data % 2;
        Node*& addHead = isOdd ? oddsHead : evensHead;
        Node*& addTail = isOdd ? oddsTail : evensTail;
        addTail = (addHead ? addTail->next : addHead) = it;
        it = it->next;
    }
    if(oddsTail) {
        oddsTail->next = nullptr;
    }
    if(evensTail) {
        evensTail->next = oddsHead;
    }
    head = evensTail ? evensHead : oddsHead;
}

Node* n() {
    return nullptr;
}

Node* n(int data, Node* next) {
    return new Node{data, next};
}

void PrintAndDestory(Node* head) {
    while(head) {
        std::cout << head->data << ' ';
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    std::cout << std::endl;
}

int main() {
    Node* head = n(1, n(5, n(2, n(700, n(1, n(6, n(4, n(7, n(1000, n())))))))));
    Rearrange(head);
    PrintAndDestory(head);

    head = n(1, n(5, n(3, n(7, n()))));
    Rearrange(head);
    PrintAndDestory(head);

    head = n(2, n(8, n(2, n(4, n(6, n())))));
    Rearrange(head);
    PrintAndDestory(head);

    head = n(1, n());
    Rearrange(head);
    PrintAndDestory(head);

    head = n(2, n());
    Rearrange(head);
    PrintAndDestory(head);

    head = n();
    Rearrange(head);
    PrintAndDestory(head);

    return 0;
}