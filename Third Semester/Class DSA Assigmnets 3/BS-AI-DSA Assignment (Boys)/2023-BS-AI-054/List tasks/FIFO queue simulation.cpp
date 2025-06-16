#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> ticketQueue;
    int ticketNumber = 1;  // Start ticket numbering from 1
    string command;

    while (true) {
        cout << "\nEnter command (take, serve, display, exit): ";
        cin >> command;

        if (command == "take") {
            ticketQueue.push_back(ticketNumber);
            cout << "Ticket " << ticketNumber << " taken.\n";
            ticketNumber++;
        } 
        else if (command == "serve") {
            if (!ticketQueue.empty()) {
                cout << "Serving ticket " << ticketQueue.front() << ".\n";
                ticketQueue.pop_front();
            } else {
                cout << "No tickets to serve.\n";
            }
        } 
        else if (command == "display") {
            if (ticketQueue.empty()) {
                cout << "No tickets in the queue.\n";
            } else {
                cout << "Tickets in the queue: ";
                for (int ticket : ticketQueue) {
                    cout << ticket << " ";
                }
                cout << endl;
            }
        } 
        else if (command == "exit") {
            cout << "Exiting...\n";
            break;
        } 
        else {
            cout << "Invalid command.\n";
        }
    }
    return 0;
}
