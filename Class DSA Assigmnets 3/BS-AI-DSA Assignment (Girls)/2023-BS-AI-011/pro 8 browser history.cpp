//3. Browser History:
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> history;
    int choice;
    string page;

    do {
        cout << "1. Visit page\n2. Go back\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter page URL: ";
            cin >> page;
            history.push(page);
        } else if (choice == 2 && !history.empty()) {
            cout << "Going back from: " << history.top() << endl;
            history.pop();
        }
    } while (choice != 3);
    return 0;
}