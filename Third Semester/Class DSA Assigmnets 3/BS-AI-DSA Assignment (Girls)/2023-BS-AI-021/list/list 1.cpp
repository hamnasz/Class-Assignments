#include <iostream>
#include <string>
using namespace std;
using namespace std;

struct Node {
    string item;
    Node* next;

    Node(const string& itemName) : item(itemName), next(nullptr) {}
};

void addItem(Node*& head, const string& itemName) {
    Node* newNode = new Node(itemName);
    newNode->next = head; 
    head = newNode;
    cout << "Added: " << itemName <<endl;
}

void removeItem(Node*& head, const std::string& itemName) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->item != itemName) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Item not found: " << itemName <<endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    cout << "Removed: " << itemName <<endl;
}

void displayList(Node* head) {
    if (head == nullptr) {
        cout << "The shopping list is empty." <<endl;
        return;
    }

    cout << "Shopping List:" <<endl;
    Node* current = head;
    while (current != nullptr) {
        cout << "- " << current->item <<endl;
        current = current->next;
    }
}

int main() {
    Node* head = nullptr; 
    string command;
    string itemName;

    while (true) {
        cout << "\nCommands: add <item>, remove <item>, display, exit" <<endl;
        cout << "Enter command: ";
        getline(cin, command);

        if (command.substr(0, 4) == "add ") {
            itemName = command.substr(4);
            addItem(head, itemName);
        } else if (command.substr(0, 7) == "remove ") {
            itemName = command.substr(7);
            removeItem(head, itemName);
        } else if (command == "display") {
            displayList(head);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Please try again." <<endl;
        }
    }

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
