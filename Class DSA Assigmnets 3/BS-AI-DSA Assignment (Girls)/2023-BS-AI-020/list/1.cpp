#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> shoppingList;
    string item;
    int choice;

    do {
        cout << "1. Add item\n2. Remove item\n3. Display list\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item to add: ";
                cin >> item;
                shoppingList.push_back(item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                cin >> item;
                shoppingList.remove(item);
                break;
            case 3:
                cout << "Current shopping list:\n";
                for (const auto& it : shoppingList) {
                    cout << it << " ";
                }
                cout << endl;
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
