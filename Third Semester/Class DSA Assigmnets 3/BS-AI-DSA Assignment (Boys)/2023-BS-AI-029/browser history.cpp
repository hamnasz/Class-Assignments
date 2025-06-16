#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history; // Stack to hold the browsing history
    string currentPage;   // Variable to store the current page
    char choice;          // Variable to store user choice

    while (true) {
        cout << "Current Page: " << (currentPage.empty() ? "None" : currentPage) << endl;
        cout << "Options: \n";
        cout << "1. Visit a new page\n";
        cout << "2. Go back to the previous page\n";
        cout << "3. Exit\n";
        cout << "Choose an option (1-3): ";
        cin >> choice;

        if (choice == '1') {
            string newPage;
            cout << "Enter the URL of the new page: ";
            cin >> newPage;

            // Push the current page to history before visiting a new one
            if (!currentPage.empty()) {
                history.push(currentPage);
            }
            currentPage = newPage; // Set the current page to the new page
        } 
        else if (choice == '2') {
            if (!history.empty()) {
                // Pop the top page from history
                currentPage = history.top();
                history.pop();
            } else {
                cout << "No previous page in history." << endl;
            }
        } 
        else if (choice == '3') {
            cout << "Exiting the browser simulation." << endl;
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl; // For better readability
    }

    return 0;
}
