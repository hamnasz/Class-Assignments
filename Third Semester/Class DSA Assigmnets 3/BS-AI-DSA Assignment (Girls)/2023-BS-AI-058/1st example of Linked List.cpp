#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> shoppingList;
    string item;
    int choice;

    do {
        cout << "1. Add Item\n2. Remove Item\n3. Display List\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter item to add: ";
            cin >> item;
            shoppingList.push_back(item);
        } else if (choice == 2) {
            cout << "Enter item to remove: ";
            cin >> item;
            shoppingList.remove(item);
        } else if (choice == 3) {
            cout << "Shopping List: ";
            for (string &i : shoppingList) {
                cout << i << " ";
            }
            cout << endl;
        }
    } while (choice != 4);

    return 0;
}
