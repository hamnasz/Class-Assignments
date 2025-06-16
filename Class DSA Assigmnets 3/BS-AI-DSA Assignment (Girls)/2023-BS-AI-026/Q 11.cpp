#include <iostream>
using namespace std;

// Node structure
struct Node {
    string data;
    Node* next;
};

// Linked list class
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    // Add item to list
    void add(string item) {
        Node* newNode = new Node();
        newNode->data = item;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Remove item from list
    void remove(string item) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        if (head->data == item) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->next->data == item) {
                Node* nodeToRemove = temp->next;
                temp->next = temp->next->next;
                delete nodeToRemove;
                return;
            }
            temp = temp->next;
        }

        cout << "Item not found in list." << endl;
    }

    // Display list
    void display() {
        Node* temp = head;
        cout << "Shopping list:" << endl;
        while (temp != nullptr) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

int main() {
    LinkedList shoppingList;

    int choice;
    string item;

    do {
        cout << "Shopping list menu:" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Display list" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item to add: ";
                cin.ignore();
                getline(cin, item);
                shoppingList.add(item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                cin.ignore();
                getline(cin, item);
                shoppingList.remove(item);
                break;
            case 3:
                shoppingList.display();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

