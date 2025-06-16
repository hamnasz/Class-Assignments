#include <iostream>
#include <string>
using namespace std;

struct Node {
    string item;
    Node* next;
};

// Function to add an item to the shopping list
void addItem(Node*& head, const string& newItem) {
    Node* newNode = new Node{newItem, head};
    head = newNode;
    cout <<"\n"<< newItem << " has been added to the shopping list.\n";
}

// Function to remove an item from the shopping list
void removeItem(Node*& head, const string& itemToRemove) {
    Node *current = head, *prev = nullptr;

    while (current != nullptr && current->item != itemToRemove) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {  // Item found
        if (prev == nullptr) {
            head = head->next;  // Item is at head
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << itemToRemove << " has been removed from the shopping list.\n";
    } else {
        cout << itemToRemove << " is not in the shopping list.\n";
    }
}

// Function to display the shopping list
void displayList(Node* head) {
    if (!head) {
        cout << "\nThe shopping list is empty.\n";
    } else {
        cout << "\nShopping list:\n";
        for (Node* current = head; current != nullptr; current = current->next) {
            cout << "- " << current->item << "\n";
        }
    }
}

int main() {
    Node* shoppingList = nullptr;
    string command, item;

    while (true) {
        cout << "\nEnter command (add, remove, display, exit): ";
        cin >> command;

        if (command == "add") {
            cout << "Enter item to add: ";
            cin.ignore();
            getline(cin, item);
            addItem(shoppingList, item);
        } else if (command == "remove") {
            cout << "Enter item to remove: ";
            cin.ignore();
            getline(cin, item);
            removeItem(shoppingList, item);
        } else if (command == "display") {
            displayList(shoppingList);
        } else if (command == "exit") {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid command.\n";
        }
    }

    // Clean up memory
    while (shoppingList != nullptr) {
        Node* temp = shoppingList;
        shoppingList = shoppingList->next;
        delete temp;
    }

    return 0;
}
