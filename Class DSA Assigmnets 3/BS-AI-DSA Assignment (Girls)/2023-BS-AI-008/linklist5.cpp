#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

bool search(Node* head, int key) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == key) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int main() {
    Node* head = nullptr;
    head = new Node{10, nullptr};
    head->next = new Node{20, nullptr};
    head->next->next = new Node{30, nullptr};

    int key = 20;
    if (search(head, key)) {
        cout << "Element " << key << " is found in the linked list." << endl;
    } else {
        cout << "Element " << key << " is not found in the linked list." << endl;
    }

    return 0;
}
