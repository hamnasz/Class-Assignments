#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;
    string command;

    while (true) {
        cout << "Enter command (visit, back, exit): ";
        cin >> command;

        if (command == "visit") {
            string url;
            cout << "Enter URL to visit: ";
            cin.ignore(); // To ignore any leftover newline
            getline(cin, url);
            history.push(url);
            cout << "Visited: " << url << endl;

        } else if (command == "back") {
            if (!history.empty()) {
                cout << "Going back from: " << history.top() << endl;
                history.pop();
                if (!history.empty()) {
                    cout << "Current page: " << history.top() << endl;
                } else {
                    cout << "No more history. You're on a blank page.\n";
                }
            } else {
                cout << "No history to go back to.\n";
            }

        } else if (command == "exit") {
            break;

        } else {
            cout << "Invalid command. Please enter 'visit', 'back', or 'exit'.\n";
        }
    }

    return 0;
}
