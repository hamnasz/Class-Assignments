#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> shoppingList;
    int choice;
    string item;

    do {
        cout << "1. Add item\n2. Remove item\n3. Show list\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter item: ";
            cin >> item;
            shoppingList.push_back(item);
        } else if (choice == 2) {
            cout << "Enter item to remove: ";
            cin >> item;
            shoppingList.remove(item);
        } else if (choice == 3) {
            cout << "Shopping List:\n";
            for (const string &i : shoppingList) cout << i << endl;
        }
    } while (choice != 4);
    return 0;
}
