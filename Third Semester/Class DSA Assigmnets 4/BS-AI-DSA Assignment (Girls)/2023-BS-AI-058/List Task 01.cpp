#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void add(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void remove(int value) {
        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) return; // Value not found

        if (prev == nullptr) {
            head = temp->next; // Remove head
        } else {
            prev->next = temp->next; // Bypass the node to remove
        }
        delete temp;
    }

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
    list.add(10);
    list.add(20);
    list.add(30);
    cout << "List after adding elements: ";
    list.display();

    list.remove(20);
    cout << "List after removing 20: ";
    list.display();

    return 0;
}