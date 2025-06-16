#include <iostream>
#include <list>
#include <string>
using namespace std;
class TicketQueue {
private:
    list<string> tickets; 

public:
    void takeTicket(const string& ticket) {
        tickets.push_back(ticket);
        cout << "Ticket " << ticket << " has been taken." << endl;
    }
    void serveTicket() {
        if (tickets.empty()) {
            cout << "No tickets in the queue to serve." << endl;
            return;
        }
        cout << "Serving ticket " << tickets.front() << "." << endl;
        tickets.pop_front(); 
    }
    void displayQueue() const {
        if (tickets.empty()) {
            cout << "The ticket queue is empty." << endl;
            return;
        }

        cout << "Current Ticket Queue:" << endl;
        for (const string& ticket : tickets) {
            cout << "- " << ticket << endl;
        }
    }
};

int main() {
    TicketQueue queue;
    string command, ticket;

    while (true) {
        cout << "\nEnter command (take/serve/display/exit): ";
        cin >> command;

        if (command == "take") {
            cout << "Enter ticket identifier: ";
            cin.ignore(); 
            getline(cin, ticket);
            queue.takeTicket(ticket);
        } 
        else if (command == "serve") {
            queue.serveTicket();
        } 
        else if (command == "display") {
            queue.displayQueue();
        } 
        else if (command == "exit") {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please enter 'take', 'serve', 'display', or 'exit'." << endl;
        }
    }

    return 0;
}