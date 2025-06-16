#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> queue;

    queue.push_back("Ticket1");
    queue.push_back("Ticket2");

    if (!queue.empty()) {
        cout << "Serving " << queue.front() << endl;
        queue.pop_front();
    }

    return 0;
}
