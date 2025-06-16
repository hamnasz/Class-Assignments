#include <iostream>
#include <string>

using namespace std;

struct Node {
    string item;
    Node* next;
};

class ShoppingList {
private:
    Node* head;  // The sentinel node

public:
    // Constructor initializes the sentinel node
    ShoppingList() {
        head = new Node{"", nullptr};  // Sentinel node with an empty item
    }

    // Add an item to the end of the list
    void addItem(const string& newItem) {
        Node* newNode = new Node{newItem, nullptr};
        Node* temp = head;

        while (temp->next) {  // Traverse to the end of the list
            temp = temp->next;
        }
        temp->next = newNode;  // Append the new node

        cout << newItem << " added to the shopping list.\n";
    }

    // Remove an item from the list by name
    void removeItem(const string& itemToRemove) {
        Node* current = head;

        while (current->next && current->next->item != itemToRemove) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;  // Bypass the node to remove
            delete temp;
            cout << itemToRemove << " removed from the shopping list.\n";
        } else {
            cout << itemToRemove << " not found in the shopping list.\n";
        }
    }

    // Display all items in the list
    void displayList() const {
        if (!head->next) {
            cout << "The shopping list is empty.\n";
            return;
        }

        cout << "Current shopping list:\n";
        Node* temp = head->next;
        while (temp) {
            cout << "- " << temp->item << endl;
            temp = temp->next;
        }
    }

    // Destructor to clean up the list
    ~ShoppingList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    ShoppingList shoppingList;
    int choice;
    string item;

    do {
        cout << "\nShopping List Menu:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display list\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter item to add: ";
                getline(cin, item);
                shoppingList.addItem(item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                getline(cin, item);
                shoppingList.removeItem(item);
                break;
            case 3:
                shoppingList.displayList();
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

