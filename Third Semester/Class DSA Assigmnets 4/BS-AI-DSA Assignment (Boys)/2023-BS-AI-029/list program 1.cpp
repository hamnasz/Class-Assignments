#include <iostream>

using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add a node at the end
    void add(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << value << " added to the list." << endl;
    }

    // Remove a node by value
    void remove(int value) {
        if (!head) {
            cout << "List is empty. Cannot remove " << value << "." << endl;
            return;
        }

        // If the head needs to be removed
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << value << " removed from the list." << endl;
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        while (current && current->data != value) {
            previous = current;
            current = current->next;
        }

        if (!current) {
            cout << value << " not found in the list." << endl;
            return;
        }

        previous->next = current->next;
        delete current;
        cout << value << " removed from the list." << endl;
    }

    // Display the list
    void display() const {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        cout << "Linked List: ";
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Destructor to clean up memory
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    list.add(10);
    list.add(20);
    list.add(30);
    list.display();

    list.remove(20);
    list.display();

    list.remove(50); // Attempt to remove a non-existent element

    list.add(40);
    list.display();

    return 0;
}
