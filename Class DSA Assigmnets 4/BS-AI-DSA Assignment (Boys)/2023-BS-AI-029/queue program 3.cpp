#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Function to display the current queue
void displayQueue(const queue<string>& q) {
    queue<string> temp = q; // Create a temporary copy to avoid modifying the original queue
    cout << "Current queue: ";
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
}

int main() {
    queue<string> ticketQueue;
    string name;
    char choice;

    do {
        cout << "Ticket Queue System" << endl;
        cout << "1. Join the queue" << endl;
        cout << "2. Leave the queue" << endl;
        cout << "3. Display queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Enter your name: ";
                cin >> name;
                ticketQueue.push(name); // Add to the back of the queue
                cout << name << " has joined the queue." << endl;
                break;

            case '2':
                if (!ticketQueue.empty()) {
                    cout << ticketQueue.front() << " has left the queue." << endl;
                    ticketQueue.pop(); // Remove from the front of the queue
                } else {
                    cout << "The queue is empty. No one to leave." << endl;
                }
                break;

            case '3':
                displayQueue(ticketQueue); // Display the current queue
                break;

            case '4':
                cout << "Exiting the ticket queue system." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != '4');

    return 0;
}
