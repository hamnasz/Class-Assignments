#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> ticketQueue;
    string ticket;
    int choice;

    do {
        cout << "1. Take a ticket\n2. Serve a ticket\n3. Display queue\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ticket name: ";
                cin >> ticket;
                ticketQueue.push_back(ticket);
                break;
            case 2:
                if (!ticketQueue.empty()) {
                    cout << "Served ticket: " << ticketQueue.front() << endl;
                    ticketQueue.pop_front();
                } else {
                    cout << "No tickets in the queue.\n";
                }
                break;
            case 3:
                cout << "Current ticket queue:\n";
                for (const auto& t : ticketQueue) {
                    cout << t << " ";
                }
                cout << endl;
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
