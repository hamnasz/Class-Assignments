#include <iostream>
#include <string>
using namespace std;

const int MAX_ITEMS = 100;  // Maximum number of items in the shopping list
string shoppingList[MAX_ITEMS];  // Array to store shopping list items
int itemCount = 0;  // Counter to track the number of items in the list

void addItem(const string& item) {
    if (itemCount < MAX_ITEMS) {
        shoppingList[itemCount++] = item;
        cout << "Item \"" << item << "\" added to the shopping list.\n";
    } else {
        cout << "The shopping list is full.\n";
    }
}

void removeItem(const string& item) {
    bool found = false;
    for (int i = 0; i < itemCount; ++i) {
        if (shoppingList[i] == item) {
            found = true;
            // Shift items to the left to fill the gap
            for (int j = i; j < itemCount - 1; ++j) {
                shoppingList[j] = shoppingList[j + 1];
            }
            --itemCount;
            cout << "Item \"" << item << "\" removed from the shopping list.\n";
            break;
        }
    }
    if (!found) {
        cout << "Item \"" << item << "\" not found in the shopping list.\n";
    }
}

void displayList() {
    if (itemCount == 0) {
        cout << "The shopping list is empty.\n";
    } else {
        cout << "Shopping List:\n";
        for (int i = 0; i < itemCount; ++i) {
            cout << "- " << shoppingList[i] << endl;
        }
    }
}

int main() {
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
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter item to add: ";
                getline(cin, item);
                addItem(item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                getline(cin, item);
                removeItem(item);
                break;
            case 3:
                displayList();
                break;
            case 4:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid option. Please choose again.\n";
                break;
        }
    }
}