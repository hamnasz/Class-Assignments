#include <iostream>
#include <list>
#include <string>

class TicketQueue {
private:
    std::list<int> queue;
    int nextTicketNumber = 1; // Keeps track of the next ticket number to be issued

public:
    // Add a ticket to the end of the queue
    void takeTicket() {
        queue.push_back(nextTicketNumber);
        std::cout << "Ticket " << nextTicketNumber << " taken." << std::endl;
        nextTicketNumber++;
    }

    // Serve the ticket at the front of the queue
    void serveTicket() {
        if (queue.empty()) {
            std::cout << "No tickets to serve." << std::endl;
        } else {
            int ticketNumber = queue.front();
            queue.pop_front();
            std::cout << "Serving ticket " << ticketNumber << "." << std::endl;
        }
    }

    // Display the current queue
    void displayQueue() const {
        if (queue.empty()) {
            std::cout << "The queue is empty." << std::endl;
        } else {
            std::cout << "Current queue: ";
            for (const int& ticket : queue) {
                std::cout << ticket << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    TicketQueue ticketQueue;
    int choice;

    do {
        std::cout << "\n1. Take a ticket\n2. Serve a ticket\n3. Display queue\n4. Exit\nChoose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                ticketQueue.takeTicket();
                break;
            case 2:
                ticketQueue.serveTicket();
                break;
            case 3:
                ticketQueue.displayQueue();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
