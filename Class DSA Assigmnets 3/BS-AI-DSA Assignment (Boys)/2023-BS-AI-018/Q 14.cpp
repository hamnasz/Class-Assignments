#include <iostream>
#include <list>

using namespace std;

class TicketQueue {
private:
    list<int> tickets;
    int ticketNumber;

public:
    TicketQueue() : ticketNumber(1) {}

    // Take a ticket (add to the end)
    void takeTicket() {
        tickets.push_back(ticketNumber);
        cout << "Ticket " << ticketNumber << " has been taken." << endl;
        ticketNumber++;
    }

    // Serve a ticket (remove from the front)
    void serveTicket() {
        if (tickets.empty()) {
            cout << "No tickets in the queue." << endl;
        } else {
            cout << "Now serving ticket " << tickets.front() << "." << endl;
            tickets.pop_front();
        }
    }

    // Display the current queue
    void displayQueue() {
        if (tickets.empty()) {
            cout << "No tickets in the queue." << endl;
        } else {
            cout << "Current queue: ";
            for (int ticket : tickets) {
                cout << ticket << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    TicketQueue ticketQueue;

    while (true) {
        cout << "Ticketing System Menu:" << endl;
        cout << "1. Take a ticket" << endl;
        cout << "2. Serve a ticket" << endl;
        cout << "3. Display queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                ticketQueue.takeTicket();
                break;
            case 2:
                ticketQueue.serveTicket();
                break;
            case 3:
                ticketQueue.displayQueue();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
