#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> history;
    string currentPage;
    int choice;

    do {
        cout << "1. Visit new page\n2. Go back\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter URL: ";
            cin >> currentPage;
            history.push(currentPage);
            cout << "You are now on: " << currentPage << endl;
        } else if (choice == 2) {
            if (!history.empty()) {
                history.pop();
                if (!history.empty()) {
                    cout << "You are now on: " << history.top() << endl;
                } else {
                    cout << "No more history to go back to." << endl;
                }
            } else {
                cout << "No history available." << endl;
            }
        }
    } while (choice != 3);

    return 0;
}

