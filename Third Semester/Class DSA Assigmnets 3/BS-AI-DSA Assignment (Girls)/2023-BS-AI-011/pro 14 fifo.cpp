//fifo

#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> queue;
    int choice;

    while (true) {
        cout << "1. Take a ticket\n2. Serve a ticket\n3. Display queue\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                int ticketNumber;
                cout << "Enter ticket number: ";
                cin >> ticketNumber;
                queue.push_back(ticketNumber);
                cout << "Ticket number " << ticketNumber << " added to queue.\n";
                break;
            }
            case 2: {
                if (queue.empty()) {
                    cout << "No tickets to serve.\n";
                } else {
                    cout << "Serving ticket number " << queue.front() << endl;
                    queue.pop_front();
                }
                break;
            }
            case 3: {
                if (queue.empty()) {
                    cout << "Queue is empty.\n";
                } else {
                    cout << "Queue:\n";
                    for (int ticket : queue) {
                        cout << "- " << ticket << endl;
                    }
                }
                break;
            }
            case 4:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}