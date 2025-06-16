#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void deleteFromBeginning(Node*& head) {
    if (head == nullptr) {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

void display(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;
    head = new Node{10, nullptr};
    head->next = new Node{20, nullptr};
    head->next->next = new Node{30, nullptr};

    cout << "Linked List before deletion: ";
    display(head);

    deleteFromBeginning(head);
    cout << "Linked List after deleting from beginning: ";
    display(head);

    return 0;
}
