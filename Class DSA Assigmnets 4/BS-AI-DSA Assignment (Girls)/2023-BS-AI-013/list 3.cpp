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
void insertAtBeginning(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == nullptr) {
        *head = newNode;
    } else {
        newNode->next = *head;
        *head = newNode;
    }
}
void insertAtEnd(Node** head, int value) {
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
void insertAtMiddle(Node** head, int value, int pos) {
    Node* newNode = createNode(value);
    if (*head == nullptr) {
        *head = newNode;
    } else if (pos == 0) {
        insertAtBeginning(head, value);
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
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    cout << "Linked List: ";
    displayList(head);
    insertAtBeginning(&head, 5);

    cout << "After inserting 5 at the beginning: ";
    displayList(head);
    insertAtMiddle(&head, 25, 2);

    cout << "After inserting 25 at position 2: ";
    displayList(head);

    return 0;
}