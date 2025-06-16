#include <iostream>
using namespace std;

const int MAX_QUEUE_SIZE = 100;
int queue[MAX_QUEUE_SIZE];
int front = 0;  // Index of the first element in the queue
int back = 0;   // Index where the next element will be added
int ticketNumber = 1;  // To keep track of ticket numbers

void takeTicket() {
    if (back < MAX_QUEUE_SIZE) {
        queue[back++] = ticketNumber++;
        cout << "Ticket " << queue[back - 1] << " taken.\n";
    } else {
        cout << "The queue is full. No more tickets can be taken.\n";
    }
}

void serveTicket() {
    if (front == back) {
        cout << "No tickets to serve.\n";
    } else {
        cout << "Serving ticket " << queue[front++] << ".\n";
        if (front == back) {
            front = back = 0;  // Reset queue when all tickets are served
        }
    }
}

void displayQueue() {
    if (front == back) {
        cout << "The queue is empty.\n";
    } else {
        cout << "Tickets in queue:\n";
        for (int i = front; i < back; i++) {
            cout << queue[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Take a ticket\n";
        cout << "2. Serve a ticket\n";
        cout << "3. Display queue\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                takeTicket();
                break;
            case 2:
                serveTicket();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid option. Please choose again.\n";
                break;
        }
    }
}