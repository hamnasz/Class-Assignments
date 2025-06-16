#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
};

// Class for the linked list
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
            head = newNode; // If the list is empty, new node becomes the head
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode; // Add the new node at the end of the list
        }
        cout << "Element " << value << " added to the list.\n";
    }

    // Function to remove an element from the list
    void removeElement(int value) {
        if (head == nullptr) {
            cout << "List is empty. Cannot remove element.\n";
            return;
        }

        // If the head needs to be removed
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Element " << value << " removed from the list.\n";
            return;
        }

        // Traverse the list to find the node to remove
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

    // Function to display all elements in the list
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

    // Destructor to clean up memory
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function to test the linked list
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
