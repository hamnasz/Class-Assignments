#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<string> ticketQueue;

    // People entering the queue
    ticketQueue.push("Alice");
    ticketQueue.push("Bob");
    ticketQueue.push("Charlie");

    cout << "People in the queue: ";
    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " ";
        ticketQueue.pop();
    }
    cout << endl;

    return 0;
}