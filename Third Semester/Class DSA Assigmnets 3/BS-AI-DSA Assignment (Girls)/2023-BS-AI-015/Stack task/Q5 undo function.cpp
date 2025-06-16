#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    stack<string> undoFunction;
    string choice;
    int option;
    while(true) {
        cout << "1.add text\n";
        cout << "2.undo\n";
        cout << "3.exit\n";
        cout << "choose option: ";
        cin >> option;
        if(option == 1) {
            cout << "enter text: ";
            cin.ignore();
            getline(cin, choice);
            undoFunction.push(choice);
        } else if(option == 2) {
            if(undoFunction.empty()) {
                cout << "empty\n";
            } else {
                cout << "Undoing: " << undoFunction.top() << endl;
                undoFunction.pop();
            }
        } else if(option == 3) {
            break;
        } else {
            cout << "invalid choice\n";
        }
    }
}
