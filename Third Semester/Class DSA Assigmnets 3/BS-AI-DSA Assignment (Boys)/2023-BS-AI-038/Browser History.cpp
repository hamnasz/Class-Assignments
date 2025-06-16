#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> forward, backward;
    string currentPage = "Home";
    
    while (true) {
        cout << "Current page: " << currentPage << endl;
        cout << "1. Visit new page\n2. Go back\n3. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string newPage;
            cout << "Enter new page: ";
            cin >> newPage;
            backward.push(currentPage);
            currentPage = newPage;
            while (!forward.empty()) forward.pop();
        } else if (choice == 2) {
            if (!backward.empty()) {
                forward.push(currentPage);
                currentPage = backward.top();
                backward.pop();
            } else {
                cout << "No previous page." << endl;
            }
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}