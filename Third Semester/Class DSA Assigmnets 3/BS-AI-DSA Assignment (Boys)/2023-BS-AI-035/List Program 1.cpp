#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> groceryList;
    string action;
    while (true) {
        cout << "Enter action (add/remove/show/quit): ";
        cin >> action;
        if (action == "add") {
            string itemToAdd;
            cout << "Type the item you want to add: ";
            cin >> itemToAdd;
            groceryList.push_back(itemToAdd);
        } else if (action == "remove") {
            string itemToRemove;
            cout << "Type the item you want to remove: ";
            cin >> itemToRemove;
            groceryList.remove(itemToRemove);
        } else if (action == "show") {
            cout << "Grocery list: ";
            for (const auto &item : groceryList) cout << item << " ";
            cout << endl;
        } else if (action == "quit") {
            break;
        }
    }
    return 0;
}
