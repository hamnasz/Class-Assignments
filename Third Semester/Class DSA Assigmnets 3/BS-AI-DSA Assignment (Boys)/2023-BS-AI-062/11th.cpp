#include <iostream>
#include <string>
using namespace std;

struct Node {
    string item;
    Node* next;
};

class ShoppingList {
private:
    Node* head;

public:
    ShoppingList() : head(nullptr) {}

    void addItem(const string& newItem) {
        Node* newNode = new Node{newItem, nullptr};
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

    void removeItem(const string& itemToRemove) {
        if (!head) return;

        if (head->item == itemToRemove) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* temp = head;
        while (temp->next && temp->next->item != itemToRemove) {
            temp = temp->next;
        }

        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    void displayList() const {
        Node* temp = head;
        while (temp) {
            cout << temp->item << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    ~ShoppingList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ShoppingList list;
    int choice;
    string item;

    do {
        cout << "1. Add item\n2. Remove item\n3. Display list\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item to add: ";
                cin >> item;
                list.addItem(item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                cin >> item;
                list.removeItem(item);
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
