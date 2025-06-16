//Write a program to simulate a basic ticket queue, where people enter and leave the line in the order they joined.

#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<string> ticketQueue;

    int choice;
    string name;

    while (true) {
        cout << "1. Enter the queue\n2. Leave the queue\n3. Display queue\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter your name: ";
                cin >> name;
                ticketQueue.push(name);
                cout << name << " has entered the queue.\n";
                break;
            case 2:
                if (ticketQueue.empty()) {
                    cout << "Queue is empty.\n";
                } else {
                    cout << ticketQueue.front() << " has left the queue.\n";
                    ticketQueue.pop();
                }
                break;
            case 3:
                cout << "Current queue: ";
                while (!ticketQueue.empty()) {
                    cout << ticketQueue.front() << " ";
                    ticketQueue.pop();
                }
                cout << endl;
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}