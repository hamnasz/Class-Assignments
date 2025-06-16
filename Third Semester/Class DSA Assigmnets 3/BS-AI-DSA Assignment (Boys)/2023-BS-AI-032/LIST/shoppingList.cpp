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
        Node* newNode = new Node{item, head};
        head = newNode;
    }

    void removeItem(const string& item) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->item != item) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Item not found.\n";
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }

    void displayList() {
        Node* current = head;
        if (!current) {
            cout << "Shopping list is empty.\n";
            return;
        }
        while (current != nullptr) {
            cout << current->item << endl;
            current = current->next;
        }
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
    list.addItem("Milk");
    list.addItem("Eggs");
    list.addItem("Bread");
    list.displayList();
    list.removeItem("Eggs");
    list.displayList();
    return 0;
}
