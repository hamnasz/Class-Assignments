#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

bool search(Node* head, int key) {
    while (head) {
        if (head->data == key) return true;
        head = head->next;
    }
    return false;
}

int main() {
    Node* head = new Node{10, new Node{20, new Node{30, nullptr}}};

    int key = 20;
    if (search(head, key)) cout << key << " found in the list." << endl;
    else cout << key << " not found in the list." << endl;

    return 0;
}
