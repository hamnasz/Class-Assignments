#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
};

// Function to add a node at the beginning of the linked list
void insertAtBeginning(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << "Inserted " << value << " at the beginning." << endl;
}

// Function to add a node at the end of the linked list
void insertAtEnd(Node*& head, int value) {
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
    cout << "Inserted " << value << " at the end." << endl;
}

// Function to add a node in the middle of the linked list
void insertAtMiddle(Node*& head, int value, int position) {
    Node* newNode = new Node();
    newNode->data = value;

    if (position == 0) {
        insertAtBeginning(head, value);
        return;
    }

    Node* temp = head;
    int currentPos = 0;
    
    // Traverse to the position before where the new node will be inserted
    while (temp != nullptr && currentPos < position - 1) {
        temp = temp->next;
        currentPos++;
    }
    
    if (temp == nullptr) {
        cout << "Position is out of bounds, inserting at the end." << endl;
        insertAtEnd(head, value);
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
        cout << "Inserted " << value << " at position " << position << "." << endl;
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

    // Insert elements at the beginning, middle, and end
    insertAtBeginning(head, 10);
    insertAtEnd(head, 30);
    insertAtMiddle(head, 20, 1);  // Inserting 20 at position 1 (middle)
    insertAtEnd(head, 40);
    insertAtMiddle(head, 25, 2);  // Inserting 25 at position 2 (middle)

    // Display the final list
    displayList(head);

    return 0;
}
