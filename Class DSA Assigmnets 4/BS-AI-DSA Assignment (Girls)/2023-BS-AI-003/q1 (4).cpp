#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Function to add a node at the end of the list
void addNode(Node*& head, int value) {
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

// Function to remove a node by value
void removeNode(Node*& head, int value) {
    if (head == nullptr) {
        cout << "List is empty, nothing to remove." << endl;
        return;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Element " << value << " removed." << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Element " << value << " not found in the list." << endl;
    } else {
        previous->next = current->next;
        delete current;
        cout << "Element " << value << " removed." << endl;
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

    // Example operations
    addNode(head, 10);
    addNode(head, 20);
    addNode(head, 30);

    cout << "After adding elements:" << endl;
    displayList(head);

    removeNode(head, 20);
    cout << "After removing element 20:" << endl;
    displayList(head);

    removeNode(head, 40); // Attempt to remove a non-existent element

    return 0;
}
