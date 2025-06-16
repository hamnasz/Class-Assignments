#include <iostream>
#include <list>
using namespace std;

class TicketingSystem {
private:
    list<int> queue;
    int currentTicket;

public:
    TicketingSystem() : currentTicket(1) {}

    void takeTicket() {
        queue.push_back(currentTicket);
        cout << "Ticket number " << currentTicket << " taken.\n";
        currentTicket++;
    }

    void serveTicket() {
        if (queue.empty()) {
            cout << "No tickets to serve.\n";
        } else {
            cout << "Serving ticket number " << queue.front() << ".\n";
            queue.pop_front();
        }
    }

    void displayQueue() const {
        cout << "Current queue: ";
        for (int ticket : queue) {
            cout << ticket << " ";
        }
        cout << "\n";
    }
};

int main() {
    TicketingSystem system;
    int choice;

    do {
        cout << "1. Take a ticket\n2. Serve a ticket\n3. Display queue\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.takeTicket();
                break;
            case 2:
                system.serveTicket();
                break;
            case 3:
                system.displayQueue();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
