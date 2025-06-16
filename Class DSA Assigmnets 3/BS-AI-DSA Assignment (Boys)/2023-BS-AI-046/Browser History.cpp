#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> history;
    string command, page;

    while (true) {
        cout << "Enter command (visit/go_back/exit): ";
        cin >> command;
        if (command == "visit") {
            cout << "Enter page name: ";
            cin >> page;
            history.push(page);
            cout << "Visited " << page << endl;
        } else if (command == "go_back") {
            if (!history.empty()) {
                cout << "Going back from " << history.top() << endl;
                history.pop();
            } else {
                cout << "No history to go back." << endl;
            }
        } else if (command == "exit") break;
    }
    return 0;
}
