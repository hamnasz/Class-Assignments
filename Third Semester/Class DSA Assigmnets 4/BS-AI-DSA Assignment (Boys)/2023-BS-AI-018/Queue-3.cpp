#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<string> ticketQueue;
    ticketQueue.push("Person1");
    ticketQueue.push("Person2");
    ticketQueue.push("Person3");

    cout << "Ticket Queue: ";
    while (!ticketQueue.empty()) {
        cout << ticketQueue.front() << " ";
        ticketQueue.pop();
    }
    cout << endl;

    return 0;
}
