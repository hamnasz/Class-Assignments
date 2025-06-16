#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Insert in the middle (after a specific position)
    void insertAtMiddle(int value, int position) {
        Node* newNode = new Node(value);
        if (position == 0) {
            insertAtBeginning(value);
            return;
        }

        Node* temp = head;
        for (int i = 0; temp != nullptr && i < position - 1; ++i) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position out of bounds.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Display the linked list
    void display() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

int main() {
    LinkedList list;
    int choice, value, position;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert at Middle\n";
        cout << "4. Display List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter value to insert at beginning: ";
            cin >> value;
            list.insertAtBeginning(value);
        } else if (choice == 2) {
            cout << "Enter value to insert at end: ";
            cin >> value;
            list.insertAtEnd(value);
        } else if (choice == 3) {
            cout << "Enter value to insert in middle: ";
            cin >> value;
            cout << "Enter position (0 for beginning): ";
            cin >> position;
            list.insertAtMiddle(value, position);
        } else if (choice == 4) {
            cout << "Linked List: ";
            list.display();
        } else if (choice == 5) {
            cout << "Exiting.\n";
            return 0;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
