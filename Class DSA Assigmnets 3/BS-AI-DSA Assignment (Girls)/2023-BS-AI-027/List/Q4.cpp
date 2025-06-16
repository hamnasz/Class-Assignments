#include <iostream>
#include <string>

using namespace std;

struct Node {
    string ticket; // Store the ticket information (can be a name, ID, etc.)
    Node* next;    // Pointer to the next node in the queue
};

class TicketQueue {
private:
    Node* front;   // Pointer to the front of the queue
    Node* rear;    // Pointer to the rear of the queue

public:
    TicketQueue() : front(nullptr), rear(nullptr) {}

    // Take a ticket (add to the end of the queue)
    void takeTicket(const string& ticketInfo) {
        Node* newNode = new Node{ticketInfo, nullptr};
        
        if (rear) {
            rear->next = newNode;  // Link the old rear to the new node
        }
        rear = newNode;  // Update the rear pointer
        
        if (!front) {
            front = newNode;  // If the queue was empty, update front as well
        }

        cout << "Ticket taken: " << ticketInfo << endl;
    }

    // Serve a ticket (remove from the front of the queue)
    void serveTicket() {
        if (!front) {
            cout << "No tickets to serve. The queue is empty.\n";
            return;
        }

        Node* temp = front;  // Temporary pointer to hold the front node
        cout << "Serving ticket: " << front->ticket << endl;
        front = front->next;  // Move front to the next node

        if (!front) {
            rear = nullptr;  // If the queue is now empty, update rear
        }

        delete temp;  // Free the memory of the served ticket
    }

    // Display the tickets in the queue
    void displayQueue() const {
        if (!front) {
            cout << "The ticket queue is empty.\n";
            return;
        }

        cout << "Current ticket queue:\n";
        Node* temp = front;
        while (temp) {
            cout << "- " << temp->ticket << endl;
            temp = temp->next;
        }
    }

    // Destructor to clean up the queue
    ~TicketQueue() {
        while (front) {
            serveTicket();  // Use serveTicket to free nodes
        }
    }
};

int main() {
    TicketQueue ticketQueue;
    int choice;
    string ticketInfo;

    do {
        cout << "\nTicketing System Menu:\n";
        cout << "1. Take a ticket\n";
        cout << "2. Serve a ticket\n";
        cout << "3. Display queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter ticket information: ";
                getline(cin, ticketInfo);
                ticketQueue.takeTicket(ticketInfo);
                break;

            case 2:
                ticketQueue.serveTicket();
                break;

            case 3:
                ticketQueue.displayQueue();
                break;

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

