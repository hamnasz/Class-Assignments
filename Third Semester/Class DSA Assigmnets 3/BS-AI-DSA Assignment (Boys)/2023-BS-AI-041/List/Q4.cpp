#include <iostream>
#include <list>
#include <string>

using namespace std;

void displayMenu() {
    cout << "\nTicketing System Menu:" << endl;
    cout << "1. Take a Ticket" << endl;
    cout << "2. Serve a Ticket" << endl;
    cout << "3. Display Tickets" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    list<string> tickets;
    int choice;
    string ticket;

    do {
        displayMenu();
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter your ticket name: ";
                getline(cin, ticket);
                tickets.push_back(ticket);
                cout << "Ticket \"" << ticket << "\" has been taken." << endl;
                break;

            case 2:
                if (!tickets.empty()) {
                    string servedTicket = tickets.front();
                    tickets.pop_front();
                    cout << "Ticket \"" << servedTicket << "\" has been served." << endl;
                } else {
                    cout << "No tickets in the queue to serve." << endl;
                }
                break;

            case 3:
                cout << "Current Tickets in Queue:" << endl;
                if (tickets.empty()) {
                    cout << "No tickets in the queue." << endl;
                } else {
                    for (const auto& t : tickets) {
                        cout << "- " << t << endl;
                    }
                }
                break;

            case 4:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
