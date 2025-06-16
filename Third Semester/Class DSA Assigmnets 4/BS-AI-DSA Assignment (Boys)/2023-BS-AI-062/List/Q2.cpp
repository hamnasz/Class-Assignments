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

    void add(int value) {
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

    bool search(int value) {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
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
    int value, searchValue;

    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    cout << "Enter value to search: ";
    cin >> searchValue;

    if (list.search(searchValue)) {
        cout << searchValue << " found in the list.\n";
    } else {
        cout << searchValue << " not found in the list.\n";
    }

    list.display();

    return 0;
}
