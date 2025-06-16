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
}

// Function to search for an element in the linked list
bool searchElement(Node* head, int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {  // If the element is found
            return true;
        }
        temp = temp->next;
    }
    return false;  // If the element is not found
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

    // Search for an element in the list
    int elementToSearch = 20;
    if (searchElement(head, elementToSearch)) {
        cout << "Element " << elementToSearch << " found in the list." << endl;
    } else {
        cout << "Element " << elementToSearch << " not found in the list." << endl;
    }

    // Search for another element
    elementToSearch = 40;
    if (searchElement(head, elementToSearch)) {
        cout << "Element " << elementToSearch << " found in the list." << endl;
    } else {
        cout << "Element " << elementToSearch << " not found in the list." << endl;
    }

    return 0;
}
