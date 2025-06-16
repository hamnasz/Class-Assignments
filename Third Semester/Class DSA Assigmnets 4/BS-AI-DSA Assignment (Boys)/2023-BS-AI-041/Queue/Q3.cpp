#include <iostream>
#include <queue>
#include <string>
using namespace std;

void displayQueue(queue<string> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    queue<string> ticketQueue;

    ticketQueue.push("Wishaq");
    ticketQueue.push("Akbar");
    ticketQueue.push("Ali");

    cout << "Current queue: ";
    displayQueue(ticketQueue);

    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " has been served." << endl;
        ticketQueue.pop();
    }

    cout << "Queue is now empty." << endl;

    return 0;
}
