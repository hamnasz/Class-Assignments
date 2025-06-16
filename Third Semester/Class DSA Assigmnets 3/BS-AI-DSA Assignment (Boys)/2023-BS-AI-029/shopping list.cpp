#include <iostream>
#include <string>
using namespace std;

// Node structure for the linked list
struct Node {
    string item;
    Node* next;
};

// Class for the shopping list
class ShoppingList {
private:
    Node* head;

public:
    ShoppingList() : head(nullptr) {}

    // Function to add an item to the list
    void addItem(const string& item) {
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
        cout << item << " added to the shopping list." << endl;
    }

    // Function to remove an item from the list
    void removeItem(const string& item) {
        if (!head) {
            cout << "The shopping list is empty." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        // Search for the item to remove
        while (temp && temp->item != item) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << item << " not found in the shopping list." << endl;
            return;
        }

        // Item found; remove it from the list
        if (prev) {
            prev->next = temp->next;
        } else {
            head = temp->next; // Remove the head node
        }

        delete temp; // Free memory
        cout << item << " removed from the shopping list." << endl;
    }

    // Function to display the current shopping list
    void displayList() const {
        if (!head) {
            cout << "The shopping list is empty." << endl;
            return;
        }

        Node* temp = head;
        cout << "Current Shopping List:" << endl;
        while (temp) {
            cout << "- " << temp->item << endl;
            temp = temp->next;
        }
    }

    // Destructor to free memory
    ~ShoppingList() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    ShoppingList list;
    int choice;
    string item;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display list\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

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
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
