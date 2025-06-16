#include <iostream>
#include <string>
using namespace std;

struct Node {
    string item;
    Node* next;
};

void addItem(Node*& head, string item) {
    Node* newNode = new Node{item, nullptr};
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

void removeItem(Node*& head, string item) {
    if (!head) return;
    if (head->item == item) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* temp = head;
    while (temp->next && temp->next->item != item) {
        temp = temp->next;
    }
    if (temp->next) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

void displayList(Node* head) {
    while (head) {
        cout << head->item << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = nullptr;
    addItem(head, "Apples");
    addItem(head, "Bread");
    addItem(head, "Milk");
    displayList(head);
    removeItem(head, "Bread");
    displayList(head);
    return 0;
}
