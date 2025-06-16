#include <iostream>
#include <list>
#include <string>
using namespace std;

void takeTicket(list<string>& queue, string person) {
    queue.push_back(person);
    cout << person << " took a ticket." << endl;
}

void serveTicket(list<string>& queue) {
    if (!queue.empty()) {
        cout << "Serving " << queue.front() << endl;
        queue.pop_front();
    } else {
        cout << "No tickets to serve." << endl;
    }
}

void displayQueue(list<string>& queue) {
    for (string person : queue) {
        cout << person << " ";
    }
    cout << endl;
}

int main() {
    list<string> queue;
    takeTicket(queue, "Alice");
    takeTicket(queue, "Bob");
    displayQueue(queue);
    serveTicket(queue);
    displayQueue(queue);
    return 0;
}
