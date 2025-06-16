#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    stack<string> history;
    string command, page;
    while (true) {
        cout << "\nEnter command (visit/go_back/exit): ";
        cin >> command;

        if (command == "visit") {
            cout << "Enter page URL: ";
            cin >> page;
            history.push(page);
            cout << "You visited: " << page << endl;
        }
        else if (command == "go_back") {
            if (history.empty()) {
                cout << "No pages in history to go back to." << endl;
            } else {
                cout << "Going back from: " << history.top() << endl;
                history.pop();
                if (!history.empty()) {
                    cout << "Current page: " << history.top() << endl;
                } else {
                    cout << "No pages in history." << endl;
                }
            }
        }
        else if (command == "exit") {
            cout << "Exiting browser history." << endl;
            break;
        }
        else {
            cout << "Invalid command. Please enter 'visit', 'go_back', or 'exit'." << endl;
        }
    }
    return 0;
}#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    stack<string> history;
    string command, page;
    while (true) {
        cout << "\nEnter command (visit/go_back/exit): ";
        cin >> command;

        if (command == "visit") {
            cout << "Enter page URL: ";
            cin >> page;
            history.push(page);
            cout << "You visited: " << page << endl;
        }
        else if (command == "go_back") {
            if (history.empty()) {
                cout << "No pages in history to go back to." << endl;
            } else {
                cout << "Going back from: " << history.top() << endl;
                history.pop();
                if (!history.empty()) {
                    cout << "Current page: " << history.top() << endl;
                } else {
                    cout << "No pages in history." << endl;
                }
            }
        }
        else if (command == "exit") {
            cout << "Exiting browser history." << endl;
            break;
        }
        else {
            cout << "Invalid command. Please enter 'visit', 'go_back', or 'exit'." << endl;
        }
    }
    return 0;
}