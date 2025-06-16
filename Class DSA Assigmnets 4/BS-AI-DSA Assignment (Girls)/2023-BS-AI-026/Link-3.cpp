#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Function to insert at the beginning of the list
void insertAtBeginning(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Function to insert at the end of the list
void insertAtEnd(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to insert at the middle (after a specific position)
void insertAtMiddle(Node*& head, int value, int position) {
    Node* newNode = new Node();
    newNode->data = value;

    if (position == 0 || head == nullptr) { // Inserting at the beginning if position is 0
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    for (int i = 0; i < position - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position is out of bounds. Inserting at the end." << endl;
        insertAtEnd(head, value);
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to display the linked list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* temp = head;
    cout << "Linked List: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;

    // Insert at the beginning
    insertAtBeginning(head, 10);
    cout << "After inserting 10 at the beginning:" << endl;
    displayList(head);

    // Insert at the end
    insertAtEnd(head, 30);
    cout << "After inserting 30 at the end:" << endl;
    displayList(head);

    // Insert at the middle (position 1)
    insertAtMiddle(head, 20, 1);
    cout << "After inserting 20 at position 1:" << endl;
    displayList(head);

    // Insert at the middle (out of bounds position, should add at end)
    insertAtMiddle(head, 40, 10);
    cout << "After attempting to insert 40 at an out-of-bounds position (inserted at end):" << endl;
    displayList(head);

    return 0;
}
