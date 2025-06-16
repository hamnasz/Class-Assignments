#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> shopList;
    string com;
    while(true) {
        cout << "Enter command (add/remove/display/exit): ";
        cin >> com;
        if(com == "add") {
            string item;
            cout << "Enter item to add: ";
            cin >> item;
            shopList.push_back(item);
        } else if(com == "remove") {
            string item;
            cout << "Enter item to remove: ";
            cin >> item;
            shopList.remove(item);
        } else if(com == "display") {
            cout << "Shopping list: ";
            for(auto &item : shopList) cout << item << " ";
            cout << endl;
        } else if(com == "exit") {
            break;
        }
    }
    return 0;
}
