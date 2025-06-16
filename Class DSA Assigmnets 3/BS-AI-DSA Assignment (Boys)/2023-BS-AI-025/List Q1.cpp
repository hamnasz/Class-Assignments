#include <iostream>
#include <list>
using namespace std;
int main() {
    list<string> shopping;
    string choice,item;
    while(true) {
        cout << "Enter your choice (add/remove/display/exit): ";
        cin >> choice;
        if(choice == "add") {
            cout << "Enter item to add: ";
            cin >> item;
            shopping.push_back(item);
        } else if(choice == "remove") {
            string item;
            cout << "Enter item to remove: ";
            cin >> item;
            shopping.remove(item);
        } else if(choice == "display") {
            cout << "Shopping list: ";
            for(auto &item : shopping) cout << item << " ";
            cout << endl;
        } else if(choice == "exit") {
            break;
        }
    }
    return 0;
}
