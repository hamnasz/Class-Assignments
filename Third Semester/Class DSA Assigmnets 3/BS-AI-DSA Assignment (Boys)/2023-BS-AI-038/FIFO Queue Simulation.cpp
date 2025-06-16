#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> queue;
    
    while (true) {
        cout << "Queue: ";
        for (auto item : queue) {
            cout << item << " ";
        }
        cout << endl;
        cout << "1. Take a ticket\n2. Serve a ticket\n3. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string ticket;
            cout << "Enter ticket number: ";
            cin >> ticket;
            queue.push_back(ticket);
        } else if (choice == 2) {
            if (!queue.empty()) {
                cout << "Serving ticket " << queue.front() << endl;
                queue.pop_front();
            } else {
                cout << "No tickets in queue." << endl;
            }
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}