#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    Node* head;

    LinkedList() { head = nullptr; }

    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Insert at the middle (after the second node for this example)
    void insertAtMiddle(int value) {
        if (head == nullptr || head->next == nullptr) {
            insertAtEnd(value);  // If less than 2 nodes, insert at end
            return;
        }

        Node* newNode = new Node();
        newNode->data = value;

        Node* temp = head;
        int count = 1;
        while (temp != nullptr && count < 2) {
            temp = temp->next;
            count++;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Display all elements
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;

    list.insertAtBeginning(10);
    list.insertAtEnd(50);
    list.insertAtMiddle(30);

    cout << "List after inserting elements at beginning, middle, and end: ";
    list.display();

    return 0;
}
