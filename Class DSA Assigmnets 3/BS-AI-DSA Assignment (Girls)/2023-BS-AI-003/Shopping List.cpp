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
        Node* newNode = new Node();
        newNode->item = newItem;
        newNode->next = head;
        head = newNode;
        cout << newItem << " has been added to the shopping list." << endl;
    }
    void removeItem(const string& itemToRemove) {
        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr && temp->item != itemToRemove) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Item not found in the list." << endl;
            return;
        }
        if (prev == nullptr) { 
            head = head->next;
        } else {
            prev->next = temp->next;
        }

        delete temp;
        cout << itemToRemove << " has been removed from the shopping list." << endl;
    }
    void displayList() const {
        if (head == nullptr) {
            cout << "The shopping list is empty." << endl;
            return;
        }
        Node* temp = head;
        cout << "Shopping List:" << endl;
        while (temp != nullptr) {
            cout << "- " << temp->item << endl;
            temp = temp->next;
        }
    }
    ~ShoppingList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ShoppingList list;
    string command, item;

    while (true) {
        cout << "\nEnter command (add/remove/display/exit): ";
        cin >> command;
        if (command == "add") {
            cout << "Enter item to add: ";
            cin.ignore();
            getline(cin, item);
            list.addItem(item);
        } 
        else if (command == "remove") {
            cout << "Enter item to remove: ";
            cin.ignore();
            getline(cin, item);
            list.removeItem(item);
        } 
        else if (command == "display") {
            list.displayList();
        } 
        else if (command == "exit") {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please enter 'add', 'remove', 'display', or 'exit'." << endl;
        }
    }
    return 0;
}