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

    // Add a node at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        cout << value << " inserted at the beginning." << endl;
    }

    // Add a node at the end
    void insertAtEnd(int value) {
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
        cout << value << " inserted at the end." << endl;
    }

    // Add a node in the middle
    void insertInMiddle(int value) {
        Node* newNode = new Node(value);
        if (!head || head->next == nullptr) {
            // If the list is empty or has only one element, add to the end
            insertAtEnd(value);
            return;
        }

        Node* slow = head;
        Node* fast = head;
        Node* prev = nullptr;

        // Use slow and fast pointers to find the middle
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        newNode->next = slow;
        prev->next = newNode;
        cout << value << " inserted in the middle." << endl;
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

    // Inserting elements
    list.insertAtEnd(10);
    list.insertAtEnd(30);
    list.display();

    list.insertAtBeginning(5);
    list.display();

    list.insertInMiddle(20);
    list.display();

    list.insertAtEnd(40);
    list.display();

    return 0;
}
