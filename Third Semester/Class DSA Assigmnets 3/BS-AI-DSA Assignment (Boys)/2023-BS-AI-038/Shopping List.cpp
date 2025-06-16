#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> shoppingList;
    
    while (true) {
        cout << "Shopping list: ";
        for (auto item : shoppingList) {
            cout << item << " ";
        }
        cout << endl;
        cout << "1. Add item\n2. Remove item\n3. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string item;
            cout << "Enter item to add: ";
            cin >> item;
            shoppingList.push_back(item);
        } else if (choice == 2) {
            string item;
            cout << "Enter item to remove: ";
            cin >> item;
            shoppingList.remove(item);
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}