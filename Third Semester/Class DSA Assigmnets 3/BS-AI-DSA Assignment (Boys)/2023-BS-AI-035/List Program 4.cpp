#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> ticketLine; // Queue for tickets
    string action, name;

    while (true) {
        cout << "\nChoose an action (take/serve/show/quit): ";
        cin >> action;

        if (action == "take") {
            cout << "Enter your name to take a ticket: ";
            cin.ignore(); // Ignore leftover newline character
            getline(cin, name); // Allow spaces in names
            ticketLine.push_back(name);
            cout << name << " has taken a ticket." << endl;
        } 
        else if (action == "serve") {
            if (!ticketLine.empty()) {
                // Serve the first ticket
                string servedName = ticketLine.front();
                ticketLine.pop_front();
                cout << servedName << " has been served." << endl;
            } else {
                cout << "No tickets available to serve." << endl;
            }
        } 
        else if (action == "show") {
            if (!ticketLine.empty()) {
                cout << "Current Ticket Queue: ";
                for (const auto& ticket : ticketLine) {
                    cout << ticket << " | ";
                }
                cout << endl;
            } else {
                cout << "The ticket queue is empty." << endl;
            }
        } 
        else if (action == "quit") {
            break;
        } 
        else {
            cout << "Invalid action. Please try again." << endl;
        }
    }

    return 0;
}
