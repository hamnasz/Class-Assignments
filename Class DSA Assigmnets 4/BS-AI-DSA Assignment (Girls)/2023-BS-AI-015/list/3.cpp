#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}
void AtBeginning(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == nullptr) {
        *head = newNode;
    } else {
        newNode->next = *head;
        *head = newNode;
    }
}
void AtEnd(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == nullptr) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void AtMiddle(Node** head, int value, int pos) {
    Node* newNode = createNode(value);
    if (*head == nullptr) {
        *head = newNode;
    } else if (pos == 0) {
        AtBeginning(head, value);
    } else {
        Node* temp = *head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}
void displayList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
int main() {
    Node* head = nullptr;
    AtEnd(&head, 2);
    AtEnd(&head, 5);
    AtEnd(&head, 3);
    cout << "Linked List: ";
    displayList(head);
    AtBeginning(&head, 6);
	cout << "After inserting 6 at the beginning: ";
    displayList(head);
    AtMiddle(&head, 15, 2);
    cout << "After inserting 15 at position 2: ";
    displayList(head);
}