#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // Maximum size of the ticket queue

class TicketQueue {
private:
    string queue[MAX_SIZE]; // Array to store the queue
    int front; // Index of the front of the queue
    int rear;  // Index of the rear of the queue
    int count; // Number of elements in the queue

public:
    TicketQueue() {
        front = 0; // Initialize front index
        rear = -1; // Initialize rear index
        count = 0; // Initialize count of elements
    }

    // Function to take a ticket
    void takeTicket(const string& name) {
        if (count == MAX_SIZE) {
            cout << "Queue is full, cannot take more tickets." << endl;
            return;
        }
        rear = (rear + 1) % MAX_SIZE; // Circular increment of rear index
        queue[rear] = name; // Add name to the queue
        count++; // Increment count
        cout << name << " has taken a ticket." << endl;
    }

    // Function to serve a ticket
    void serveTicket() {
        if (count == 0) {
            cout << "No tickets in the queue to serve." << endl;
            return;
        }
        cout << queue[front] << " has been served." << endl; // Serve the front ticket
        front = (front + 1) % MAX_SIZE; // Circular increment of front index
        count--; // Decrement count
    }

    // Function to display the ticket queue
    void displayQueue() {
        if (count == 0) {
            cout << "The ticket queue is currently empty." << endl;
            return;
        }
        cout << "Current Ticket Queue: ";
        for (int i = 0; i < count; i++) {
            cout << queue[(front + i) % MAX_SIZE] << " | "; // Display in order
        }
        cout << endl;
    }
};

int main() {
    TicketQueue ticketQueue; // Create a ticket queue
    string choice, name;

    while (true) {
        cout << "\nEnter your choice (take/serve/display/exit): ";
        cin >> choice;

        if (choice == "take") {
            cout << "Enter your name to take a ticket: ";
            cin >> name;
            ticketQueue.takeTicket(name); // Take a ticket
        } 
        else if (choice == "serve") {
            ticketQueue.serveTicket(); // Serve a ticket
        } 
        else if (choice == "display") {
            ticketQueue.displayQueue(); // Display the queue
        } 
        else if (choice == "exit") {
            break; // Exit the loop
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}