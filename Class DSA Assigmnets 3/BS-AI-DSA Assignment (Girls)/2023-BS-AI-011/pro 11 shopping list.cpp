//shopping list
#include <iostream>
#include <list>

using namespace std;

int main() {
    list<string> shoppingList;
    int choice;

    while (true) {
        cout << "1. Add item\n2. Remove item\n3. Display list\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                string item;
                cout << "Enter item: ";
                cin >> item;
                shoppingList.push_back(item);
                break;
            }
            case 2: {
                if (shoppingList.empty()) {
                    cout << "List is empty.\n";
                } else {
                    shoppingList.pop_back();
                    cout << "Last item removed.\n";
                }
                break;
            }
            case 3: {
                if (shoppingList.empty()) {
                    cout << "List is empty.\n";
                } else {
                    cout << "Shopping List:\n";
                    for (const string& item : shoppingList) {
                        cout << "- " << item << endl;
                    }
                }
                break;
            }
            case 4:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}