#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> act;
    int ch;
    string a;

    do {
        cout << "1. Perform function\n2. Undo\n3. Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Enter function: ";
            cin.ignore();
            getline(cin, a);
            act.push(a);
        } else if (ch == 2 && !act.empty()) {
            cout << "Undoing function: " << act.top() << endl;
            act.pop();
        }
    } while (ch != 3);
    return 0;
}
