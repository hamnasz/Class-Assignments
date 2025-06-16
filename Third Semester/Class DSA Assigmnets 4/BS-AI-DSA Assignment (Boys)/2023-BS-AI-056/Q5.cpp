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

// Function to search for an element in the linked list
bool searchElement(Node* head, int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;  // Element found
        }
        temp = temp->next;
    }
    return false;  // Element not found
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

    // Adding elements to the linked list
    addNode(head, 10);
    addNode(head, 20);
    addNode(head, 30);
    addNode(head, 40);

    cout << "Initial list:" << endl;
    displayList(head);

    // Searching for elements in the linked list
    int searchValue = 20;
    if (searchElement(head, searchValue)) {
        cout << "Element " << searchValue << " found in the list." << endl;
    } else {
        cout << "Element " << searchValue << " not found in the list." << endl;
    }

    searchValue = 50;
    if (searchElement(head, searchValue)) {
        cout << "Element " << searchValue << " found in the list." << endl;
    } else {
        cout << "Element " << searchValue << " not found in the list." << endl;
    }

    return 0;
}
