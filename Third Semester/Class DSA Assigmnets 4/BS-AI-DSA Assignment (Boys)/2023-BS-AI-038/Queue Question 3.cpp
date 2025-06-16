#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    queue<string> ticketQueue;
    int choice;
    string name;

    do {
        cout << "\nTicket Queue Operations:\n";
        cout << "1. Take a Ticket\n";
        cout << "2. Serve a Ticket\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter your name: ";
                cin.ignore(); 
                getline(cin, name);
                ticketQueue.push(name);
                cout << "Ticket taken for " << name << ".\n";
                break;
            case 2:
                if (ticketQueue.empty()) {
                    cout << "No tickets to serve.\n";
                } else {
                    cout << "Serving ticket for " << ticketQueue.front() << ".\n";
                    ticketQueue.pop();
                }
                break;
            case 3:
                if (ticketQueue.empty()) {
                    cout << "The queue is empty.\n";
                } else {
                    cout << "Current queue: ";
                    queue<string> tempQueue = ticketQueue;
                    while (!tempQueue.empty()) {
                        cout << tempQueue.front() << " ";
                        tempQueue.pop();
                    }
                    cout << "\n";
                }
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
