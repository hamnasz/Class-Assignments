#include <iostream>
#include <string>
using namespace std;

// Node structure for the linked list
struct Node {
    string ticketNumber;
    Node* next;
};

// Class for the queue
class TicketQueue {
private:
    Node* front;
    Node* rear;

public:
    TicketQueue() : front(nullptr), rear(nullptr) {}

    // Function to take a ticket (enqueue)
    void takeTicket(const string& ticketNumber) {
        Node* newNode = new Node{ticketNumber, nullptr};
        if (!rear) {
            front = rear = newNode; // First ticket
        } else {
            rear->next = newNode; // Add to the end
            rear = newNode;
        }
        cout << "Ticket " << ticketNumber << " taken." << endl;
    }

    // Function to serve a ticket (dequeue)
    void serveTicket() {
        if (!front) {
            cout << "No tickets in the queue." << endl;
            return;
        }

        Node* temp = front;
        cout << "Serving ticket " << front->ticketNumber << "." << endl;
        front = front->next;

        if (!front) {
            rear = nullptr; // Queue is empty
        }

        delete temp; // Free memory
    }

    // Function to display the current tickets in the queue
    void displayQueue() const {
        if (!front) {
            cout << "No tickets in the queue." << endl;
            return;
        }

        cout << "Current Ticket Queue:" << endl;
        Node* current = front;
        while (current) {
            cout << "- Ticket " << current->ticketNumber << endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~TicketQueue() {
        while (front) {
            serveTicket();
        }
    }
};

int main() {
    TicketQueue ticketQueue;
    int choice;
    string ticketNumber;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Take a ticket\n";
        cout << "2. Serve a ticket\n";
        cout << "3. Display ticket queue\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                cout << "Enter ticket number: ";
                getline(cin, ticketNumber);
                ticketQueue.takeTicket(ticketNumber);
                break;
            case 2:
                ticketQueue.serveTicket();
                break;
            case 3:
                ticketQueue.displayQueue();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
