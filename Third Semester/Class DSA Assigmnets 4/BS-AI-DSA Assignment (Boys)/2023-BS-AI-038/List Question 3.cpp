#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void addAtBeginning(int value) {
        Node* newNode = new Node{value, head};
        head = newNode;
    }

    void addAtEnd(int value) {
        Node* newNode = new Node{value, nullptr};
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void addAtMiddle(int value, int position) {
        if (position == 0) {
            addAtBeginning(value);
            return;
        }

        Node* newNode = new Node{value, nullptr};
        Node* temp = head;

        for (int i = 0; temp != nullptr && i < position - 1; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position out of bounds. Adding at the end.\n";
            addAtEnd(value);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

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
    list.addAtBeginning(10);
    list.addAtEnd(20);
    list.addAtMiddle(15, 1);
    list.addAtEnd(25);

    list.display();

    return 0;
}
