#include <iostream>
#include <queue>
using namespace std;

class TicketQueue {
public:
    queue<string> q;

    void enterQueue(string name) {
        q.push(name);
        cout << name << " has entered the queue." << endl;
    }

    void leaveQueue() {
        if (q.empty()) {
            cout << "The queue is empty." << endl;
            return;
        }
        string name = q.front();
        q.pop();
        cout << name << " has left the queue." << endl;
    }

    void displayQueue() {
        queue<string> temp = q;
        cout << "Current queue: ";
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

int main() {
    TicketQueue queue;
    queue.enterQueue("Alice");
    queue.enterQueue("Bob");
    queue.enterQueue("Charlie");
    queue.displayQueue();

    queue.leaveQueue();
    queue.displayQueue();

    return 0;
}