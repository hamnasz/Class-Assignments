#include <iostream>
#include <queue>
#include <string>
using namespace std;

class TicketQueue {
private:
    queue<string> q;  // Queue to hold the names of people in the line

public:
    // Function to add a person to the queue
    void joinQueue(const string& name) {
        q.push(name);
        cout << name << " has joined the queue." << endl;
    }

    // Function to remove a person from the queue
    void leaveQueue() {
        if (q.empty()) {
            cout << "The queue is empty. No one to leave." << endl;
            return;
        }
        cout << q.front() << " has left the queue." << endl;
        q.pop();
    }

    // Function to display the current queue
    void displayQueue() {
        if (q.empty()) {
            cout << "The queue is currently empty." << endl;
            return;
        }
        cout << "Current queue: ";
        queue<string> tempQueue = q; // Create a copy to display without modifying the original queue
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
    }
};

int main() {
    TicketQueue ticketQueue; // Create an instance of the TicketQueue
    string name;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Join the queue\n";
        cout << "2. Leave the queue\n";
        cout << "3. Display the queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter your name: ";
                cin.ignore(); // Ignore the newline character from previous input
                getline(cin, name); // Use getline to allow names with spaces
                ticketQueue.joinQueue(name);
                break;
            case 2:
                ticketQueue.leaveQueue();
                break;
            case 3:
                ticketQueue.displayQueue();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}