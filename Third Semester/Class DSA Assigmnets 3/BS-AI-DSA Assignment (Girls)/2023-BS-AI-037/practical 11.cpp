#include <iostream>
#include <string>

struct Node {
    std::string item;
    Node* next;
};

class ShoppingList {
private:
    Node* head = nullptr;

public:
    // Add an item to the end of the list
    void addItem(const std::string& item) {
        Node* newNode = new Node{item, nullptr};
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        std::cout << "Added: " << item << std::endl;
    }

    // Remove an item from the list
    void removeItem(const std::string& item) {
        if (!head) {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        if (head->item == item) {
            Node* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Removed: " << item << std::endl;
            return;
        }

        Node* current = head;
        while (current->next && current->next->item != item) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            std::cout << "Removed: " << item << std::endl;
        } else {
            std::cout << "Item not found." << std::endl;
        }
    }

    // Display the current shopping list
    void displayList() const {
        if (!head) {
            std::cout << "The shopping list is empty." << std::endl;
            return;
        }

        Node* current = head;
        std::cout << "Shopping List:" << std::endl;
        while (current) {
            std::cout << "- " << current->item << std::endl;
            current = current->next;
        }
    }

    // Destructor to clean up memory
    ~ShoppingList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ShoppingList shoppingList;
    int choice;
    std::string item;

    do {
        std::cout << "\n1. Add item\n2. Remove item\n3. Display list\n4. Exit\nChoose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter item to add: ";
                std::getline(std::cin, item);
                shoppingList.addItem(item);
                break;
            case 2:
                std::cout << "Enter item to remove: ";
                std::getline(std::cin, item);
                shoppingList.removeItem(item);
                break;
            case 3:
                shoppingList.displayList();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
