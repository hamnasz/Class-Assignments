#include <iostream>
#include <queue>
#include <string>
using namespace std;
void simulateTicketQueue() {
    queue<string> ticketQueue;
    ticketQueue.push("Faisal");
    ticketQueue.push("Hanzla");
    ticketQueue.push("Haseeb");
    ticketQueue.push("Hamza");
    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " has joined and left." << endl;
        ticketQueue.pop();
    }
}
int main() {
    simulateTicketQueue();
    return 0;
}
