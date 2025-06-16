#include <iostream>
#include <stack>
#include <string>
using namespace std;

void browserHistory() {
    stack<string> history;
    string action;

    while (true) {
        cout << "Enter 'visit' to visit a page or 'back' to go back (or 'exit' to stop): ";
        cin >> action;

        if (action == "visit") {
            string page;
            cout << "Enter page URL: ";
            cin >> page;
            history.push(page);
        } else if (action == "back") {
            if (!history.empty()) {
                history.pop();
            } else {
                cout << "No more history.\n";
            }
        } else if (action == "exit") {
            break;
        }

        cout << "Current History: ";
        stack<string> temp = history;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << "\n";
    }
}

int main() {
    browserHistory();
    return 0;
}
