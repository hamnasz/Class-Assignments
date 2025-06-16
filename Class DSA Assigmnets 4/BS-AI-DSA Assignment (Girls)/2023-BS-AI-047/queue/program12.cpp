#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<string> ticketQueue;

    // People entering the queue
    ticketQueue.push("Alice");
    ticketQueue.push("Bob");
    ticketQueue.push("Charlie");

    cout << "Processing the ticket queue:" << endl;

    // Processing people in the order they joined
    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " is served." << endl;
        ticketQueue.pop();
    }

    return 0;
}
