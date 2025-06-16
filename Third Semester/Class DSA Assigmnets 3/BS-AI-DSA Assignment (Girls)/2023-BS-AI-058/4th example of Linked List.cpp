#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> ticketQueue;
    int ticketNumber = 1;  // Start ticket number from 1
    int choice;

    do {
        cout << "1. Take Ticket\n2. Serve Ticket\n3. Display Queue\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            ticketQueue.push_back(ticketNumber);
            cout << "Ticket " << ticketNumber << " taken." << endl;
            ticketNumber++;  // Increment ticket number for the next person
        } else if (choice == 2) {
            if (!ticketQueue.empty()) {
                cout << "Serving ticket: " << ticketQueue.front() << endl;
                ticketQueue.pop_front();  // Serve the first ticket in the queue
            } else {
                cout << "No tickets to serve." << endl;
            }
        } else if (choice == 3) {
            cout << "Current Queue: ";
            for (int ticket : ticketQueue) {
                cout << ticket << " ";
            }
            cout << endl;
        }
    } while (choice != 4);

    return 0;
}
