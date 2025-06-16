#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void add(Node*& head, int data) {
    Node* newNode = new Node{data, nullptr};
    if (!head) head = newNode;
    else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void remove(Node*& head, int data) {
    if (!head) return;
    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* temp = head;
    while (temp->next && temp->next->data != data) temp = temp->next;
    if (temp->next) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

void display(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;
    add(head, 10);
    add(head, 20);
    add(head, 30);
    cout << "Linked list: ";
    display(head);

    remove(head, 20);
    cout << "After removal: ";
    display(head);

    return 0;
}
