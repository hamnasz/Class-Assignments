#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<string> ticketQueue;
    ticketQueue.push("Alice");
    ticketQueue.push("Bob");
    ticketQueue.push("Charlie");

    cout << "Serving the queue:" << endl;
    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " is being served." << endl;
        ticketQueue.pop();
    }
    return 0;
}