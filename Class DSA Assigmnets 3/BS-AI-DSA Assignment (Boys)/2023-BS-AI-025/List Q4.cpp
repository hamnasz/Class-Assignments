#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> ticketQueue;
    string choice, name;

    while (true) {
        cout << "\nEnter your choice (take/serve/display/exit): ";
        cin >> choice;

        if (choice == "take") {
            cout << "Enter your name to take a ticket: ";
            cin>>name;
            ticketQueue.push_back(name);
            cout << name << " has taken a ticket." << endl;
        } 
        else if (choice == "serve") {
            if (!ticketQueue.empty()) {
                string servedName = ticketQueue.front();
                ticketQueue.pop_front();
                cout << servedName << " has been served." << endl;
            } else {
                cout << "No tickets in the queue to serve." << endl;
            }
        } 
        else if (choice == "display") {
            if (!ticketQueue.empty()) {
                cout << "Current Ticket Queue: ";
                for (const auto& ticket : ticketQueue) {
                    cout << ticket << " | ";
                }
                cout << endl;
            } else {
                cout << "The ticket queue is currently empty." << endl;
            }
        } 
        else if (choice == "exit") {
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
