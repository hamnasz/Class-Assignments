#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> queue;
    int choice;
    int ticket = 1;

    do {
        cout << "1. Take ticket\n2. Serve ticket\n3. Show queue\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            queue.push_back(ticket++);
        } else if (choice == 2 && !queue.empty()) {
            cout << "Serving ticket: " << queue.front() << endl;
            queue.pop_front();
        } else if (choice == 3) {
            cout << "Current Queue:\n";
            for (int t : queue) cout << "Ticket " << t << endl;
        }
    } while (choice != 4);
    return 0;
}
