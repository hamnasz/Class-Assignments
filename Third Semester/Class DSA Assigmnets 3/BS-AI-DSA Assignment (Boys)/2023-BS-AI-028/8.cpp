#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> history;
    string command, url;

    while (true) {
        cout << "Enter command (visit <url> / back / exit): ";
        cin >> command;

        if (command == "visit") {
            cin >> url;
            history.push(url);
            cout << "Visited: " << url << endl;
        } else if (command == "back") {
            if (!history.empty()) {
                cout << "Going back from: " << history.top() << endl;
                history.pop();
            } else {
                cout << "No history to go back to." << endl;
            }
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}
