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

    void addItem(const string& item) {
        Node* newNode = new Node();
        newNode->item = item;
        newNode->next = head;
        head = newNode;
        cout << item << " has been added to the shopping list." << endl;
    }

    void removeItem(const string& item) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->item == item) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << item << " has been removed from the shopping list." << endl;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << item << " not found in the shopping list." << endl;
    }

    void displayList() const {
        Node* current = head;
        if (current == nullptr) {
            cout << "Shopping list is empty." << endl;
            return;
        }
        cout << "Shopping List:" << endl;
        while (current != nullptr) {
            cout << "- " << current->item << endl;
            current = current->next;
        }
    }

    ~ShoppingList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    ShoppingList list;
    int choice;
    string item;

    do {
        cout << "\nShopping List Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter item to add: ";
                getline(cin, item);
                list.addItem(item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                getline(cin, item);
                list.removeItem(item);
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
