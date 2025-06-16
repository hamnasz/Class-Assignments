#include <iostream>
#include <string>
using namespace std;

struct Node {
    string ticket;
    Node* next;
    
    Node(const string& t) : ticket(t), next(nullptr) {}
};

class TicketQueue {
private:
    Node* front;
    Node* rear;

public:
    TicketQueue() : front(nullptr), rear(nullptr) {}

    void takeTicket(const string& ticket) {
        Node* newNode = new Node(ticket);
        if (rear) {
            rear->next = newNode; 
        }
        rear = newNode; 
        if (!front) {
            front = newNode; 
        }
        cout << "Ticket taken: " << ticket <<endl;
    }

    void serveTicket() {
        if (!front) {
            cout << "No tickets to serve." <<endl;
            return;
        }
        cout << "Serving ticket: " << front->ticket <<endl;
        Node* temp = front;
        front = front->next; 
        delete temp; 
        if (!front) {
            rear = nullptr; 
        }
    }

    void displayQueue() {
        if (!front) {
            cout << "No tickets in the queue." <<endl;
            return;
        }
        cout << "Tickets in the queue:" <<endl;
        Node* current = front;
        while (current) {
            cout << "- " << current->ticket <<endl;
            current = current->next;
        }
    }
};

int main() {
    TicketQueue queue;
    string command, ticket;

    while (true) {
        cout << "\nCommands: take <ticket>, serve, display, exit" <<endl;
        cout << "Enter command: ";
        getline(cin, command);

        if (command.substr(0, 5) == "take ") {
            ticket = command.substr(5);
            queue.takeTicket(ticket);
        } else if (command == "serve") {
            queue.serveTicket();
        } else if (command == "display") {
            queue.displayQueue();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Please try again." <<endl;
        }
    }

    return 0;
}