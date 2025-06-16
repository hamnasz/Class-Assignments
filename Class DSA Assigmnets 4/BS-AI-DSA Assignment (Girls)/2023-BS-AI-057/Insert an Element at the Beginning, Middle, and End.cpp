#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertBeginning(Node*& head, int data) {
    head = new Node{data, head};
}

void insertEnd(Node*& head, int data) {
    Node* newNode = new Node{data, nullptr};
    if (!head) head = newNode;
    else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void insertMiddle(Node* head, int data, int position) {
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp; i++) temp = temp->next;
    if (temp) temp->next = new Node{data, temp->next};
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
    insertBeginning(head, 10);
    insertEnd(head, 30);
    insertMiddle(head, 20, 2);

    cout << "Linked list: ";
    display(head);

    return 0;
}
