#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {} 

    void addElement(int value) {
        Node* newNode = new Node();
        newNode->data = value;
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
        cout << "Element " << value << " added to the list.\n";
    }

    void removeElement(int value) {
        if (head == nullptr) {
            cout << "List is empty. Cannot remove element.\n";
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Element " << value << " removed from the list.\n";
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Element " << value << " not found in the list.\n";
        } else {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
            cout << "Element " << value << " removed from the list.\n";
        }
    }
    void displayList() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        cout << "Elements in the list: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;
    int choice, value;

    do {
        cout << "\nLinked List Operations:\n";
        cout << "1. Add Element\n";
        cout << "2. Remove Element\n";
        cout << "3. Display List\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the element to add: ";
                cin >> value;
                list.addElement(value);
                break;
            case 2:
                cout << "Enter the element to remove: ";
                cin >> value;
                list.removeElement(value);
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
