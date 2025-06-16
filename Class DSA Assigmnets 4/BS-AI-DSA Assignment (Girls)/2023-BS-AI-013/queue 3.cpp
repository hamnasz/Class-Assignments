#include <iostream>
#include <queue>
using namespace std;
int main() {
    queue<string> ticket;
    ticket.push("ayesha");
    ticket.push("alina");
    ticket.push("fiza");
	cout << "Serving the queue:" << endl;
    while (!ticket.empty()) {
        cout << ticket.front() << " is being served." << endl;
        ticket.pop();
    }
    return 0;
}