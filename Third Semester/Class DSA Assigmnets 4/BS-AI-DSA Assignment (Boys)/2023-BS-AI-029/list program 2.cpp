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

    // Search for an element in the list
    bool search(int value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) {
                return true; // Element found
            }
            temp = temp->next;
        }
        return false; // Element not found
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

    // Search for elements
    int searchValue = 20;
    if (list.search(searchValue)) {
        cout << searchValue << " found in the list." << endl;
    } else {
        cout << searchValue << " not found in the list." << endl;
    }

    searchValue = 40;
    if (list.search(searchValue)) {
        cout << searchValue << " found in the list." << endl;
    } else {
        cout << searchValue << " not found in the list." << endl;
    }

    return 0;
}
