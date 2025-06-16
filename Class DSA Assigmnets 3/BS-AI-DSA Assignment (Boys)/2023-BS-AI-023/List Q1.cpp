#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> shoppingList;
    string command;
    while(true) {
        cout << "Enter command (add/remove/display/exit): ";
        cin >> command;
        if(command == "add") {
            string item;
            cout << "Enter item to add: ";
            cin >> item;
            shoppingList.push_back(item);
        } else if(command == "remove") {
            string item;
            cout << "Enter item to remove: ";
            cin >> item;
            shoppingList.remove(item);
        } else if(command == "display") {
            cout << "Shopping list: ";
            for(auto &item : shoppingList) cout << item << " ";
            cout << endl;
        } else if(command == "exit") {
            break;
        }
    }
    return 0;
}
