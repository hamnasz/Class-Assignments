#include <iostream>
#include <string>
#include <queue>
using namespace std;

class TicketQueue {
private:
    queue<string> tickets;

public:
    void takeTicket(const string& name) {
        tickets.push(name);
    }

    void serveTicket() {
        if (!tickets.empty()) {
            cout << "Serving ticket for: " << tickets.front() << endl;
            tickets.pop();
        } else {
            cout << "No tickets to serve.\n";
        }
    }

    void displayQueue() {
        if (tickets.empty()) {
            cout << "No tickets in the queue.\n";
            return;
        }
        queue<string> tempQueue = tickets;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }
};

int main() {
    TicketQueue queue;
    queue.takeTicket("Alice");
    queue.takeTicket("Bob");
    queue.displayQueue();
    queue.serveTicket();
    queue.displayQueue();
    return 0;
}
