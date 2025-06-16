#include <iostream>
#include <queue>
#include <string>
using namespace std;

class TicketQueue {
private:
    queue<string> q;

public:
    // Function to add a person to the queue
    void joinQueue(const string& name) {
        q.push(name);
        cout << name << " has joined the queue." << endl;
    }

    // Function to serve the next person in the queue
    void serveNext() {
        if (q.empty()) {
            cout << "No one is in the queue to serve." << endl;
        } else {
            cout << q.front() << " has been served." << endl;
            q.pop();
        }
    }

    // Function to display the current queue
    void displayQueue() {
        if (q.empty()) {
            cout << "The queue is empty." << endl;
            return;
        }

        cout << "Current queue: ";
        queue<string> temp = q; // Copy the queue to avoid modifying the original
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

int main() {
    TicketQueue tq;
    int choice;
    string name;

    do {
        cout << "\nMenu:\n";
        cout << "1. Join Queue\n";
        cout << "2. Serve Next\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                tq.joinQueue(name);
                break;
            case 2:
                tq.serveNext();
                break;
            case 3:
                tq.displayQueue();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
