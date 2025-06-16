#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
};

// Function to add a node at the end of the linked list
void addNode(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {  // If the list is empty
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Added " << value << " to the list." << endl;
}

// Function to remove a node with a specific value
void removeNode(Node*& head, int value) {
    if (head == nullptr) {  // If the list is empty
        cout << "List is empty. Cannot remove " << value << "." << endl;
        return;
    }

    // If the node to be removed is the head
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Removed " << value << " from the list." << endl;
        return;
    }

    // Search for the node to be removed
    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {  // Value not found
        cout << value << " not found in the list." << endl;
    } else {  // Remove the node
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
        cout << "Removed " << value << " from the list." << endl;
    }
}

// Function to display the linked list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }
    Node* temp = head;
    cout << "List elements: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;  // Initialize the head of the linked list

    // Add elements to the linked list
    addNode(head, 10);
    addNode(head, 20);
    addNode(head, 30);

    // Display the list
    displayList(head);

    // Remove an element from the list
    removeNode(head, 20);

    // Display the list again
    displayList(head);

    // Try removing an element that is not in the list
    removeNode(head, 40);

    // Display the final list
    displayList(head);

    return 0;
}