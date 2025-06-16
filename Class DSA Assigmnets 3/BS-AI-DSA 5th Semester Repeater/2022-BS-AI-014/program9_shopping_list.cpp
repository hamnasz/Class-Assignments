#include <iostream>
#include <list>
#include <string>
using namespace std;

void shoppingList() {
    list<string> shopping_list;
    string action;

    while (true) {
        cout << "Enter 'add', 'remove', or 'display' (or 'exit' to stop): ";
        cin >> action;

        if (action == "add") {
            string item;
            cout << "Enter item to add: ";
            cin >> item;
            shopping_list.push_back(item);
        } else if (action == "remove") {
            string item;
            cout << "Enter item to remove: ";
            cin >> item;
            shopping_list.remove(item);
        } else if (action == "display") {
            cout << "Shopping List: ";
            for (const string& item : shopping_list) {
                cout << item << " ";
            }
            cout << "\n";
        } else if (action == "exit") {
            break;
        }
    }
}

int main() {
    shoppingList();
    return 0;
}
