#include <iostream>
#include <queue>
#include <string>
using namespace std;

void print(queue<string> q) {
    cout << "Queue: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    queue<string> ticketQueue;
    int choice;
    string name;

    while (true) {
        cout << "\nTicket Queue System\n";
        cout << "1. Join the queue\n";
        cout << "2. Serve the next person\n";
        cout << "3. Print queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                ticketQueue.push(name);
                cout << name << " has joined the Queue.\n";
                break;

            case 2:
                if (!ticketQueue.empty()) {
                    cout << ticketQueue.front() << " has left the Queue\n";
                    ticketQueue.pop();
                } 
                else {
                    cout << "The queue is empty.\n";
                }
                break;

            case 3:
                if (ticketQueue.empty()) {
                    cout << "The queue is empty.\n";
                } 
                else {
                    print(ticketQueue);
                }
                break;

            case 4:
                cout << "Exiting the program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } 

    return 0;
}
