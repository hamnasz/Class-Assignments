#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> browserHistory;
    string userCommand;

    while (true) {
        cout << "Enter command (visit, back, exit): ";
        cin >> userCommand;

        if (userCommand == "visit") {
            string website;
            cout << "Please enter the URL you want to visit: ";
            cin.ignore(); // To clear the newline character
            getline(cin, website);
            browserHistory.push(website);
            cout << "You have visited: " << website << endl;

        } else if (userCommand == "back") {
            if (!browserHistory.empty()) {
                cout << "Leaving: " << browserHistory.top() << endl;
                browserHistory.pop();
                if (!browserHistory.empty()) {
                    cout << "Current page: " << browserHistory.top() << endl;
                } else {
                    cout << "No history left. You are now on a blank page.\n";
                }
            } else {
                cout << "No previous pages to return to.\n";
            }

        } else if (userCommand == "exit") {
            break;

        } else {
            cout << "Invalid command. Please use 'visit', 'back', or 'exit'.\n";
        }
    }

    return 0;
}
