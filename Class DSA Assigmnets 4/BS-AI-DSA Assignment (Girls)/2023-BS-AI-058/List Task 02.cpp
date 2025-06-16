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

    bool search(int value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }
};

int main() {
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);

    cout << "Searching for 20: " << (list.search(20) ? "Found" : "Not Found") << endl;
    cout << "Searching for 40: " << (list.search(40) ? "Found" : "Not Found") << endl;

    return 0;
}