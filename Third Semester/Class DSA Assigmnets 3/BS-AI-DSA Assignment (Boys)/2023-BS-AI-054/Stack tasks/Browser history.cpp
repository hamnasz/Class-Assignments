#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;
    string command;
    string currentPage = ""; 

    while (true) {
        // Display the current page or "None" if no page is visited
        cout << "\nCurrent Page: " << (currentPage.empty() ? "None" : currentPage) << endl;
        cout << "Enter a command (visit <url>, back, exit): ";
        getline(cin, command);

        // Check if the command starts with "visit "
        if (command.substr(0, 6) == "visit ") {
            string url = command.substr(6); // Extract the URL
           
		    // If there is a current page, push it onto the history
            if (currentPage != "") {
                history.push(currentPage);
            }
            currentPage = url; // Update the current page
            cout << "Visited: " << currentPage << endl;
        } 
        
		// Check for the "back" command
        else if (command == "back") {
           
		    // Check if there is any page in history
            if (history.size() > 0) {
                currentPage = history.top(); // Get the last visited page
                history.pop(); // Remove it from history
                cout << "Went back to: " << currentPage << endl;
            } 
            // If no pages in history
            else {
                cout << "No pages in history to go back to." << endl;
            }
        } 
        // Check for the "exit" command
        else if (command == "exit") {
            cout << "Exiting the browser simulation." << endl;
            break; // Exit the loop
        } 
        // Handle invalid commands
        else {
            cout << "Invalid command. Please enter 'visit <url>', 'back', or 'exit'." << endl;
        }
    }

    return 0;
}
