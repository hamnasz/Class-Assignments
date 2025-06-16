#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<string> ticketQueue;
    ticketQueue.push("Alice");
    ticketQueue.push("Bob");
    ticketQueue.push("Charlie");

    cout << "Processing queue:\n";
    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " is served.\n";
        ticketQueue.pop();
    }

    return 0;
}
