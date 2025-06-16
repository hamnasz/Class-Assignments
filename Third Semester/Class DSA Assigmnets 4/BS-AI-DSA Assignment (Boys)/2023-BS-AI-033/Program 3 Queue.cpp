#include <iostream>
#include <queue>
#include <string>

int main() {
    std::queue<std::string> ticketQueue;

    // Adding people to the queue
    ticketQueue.push("Alice");
    ticketQueue.push("Bob");
    ticketQueue.push("Charlie");
    ticketQueue.push("Diana");

    std::cout << "Current queue: ";
    std::queue<std::string> tempQueue = ticketQueue;
    while (!tempQueue.empty()) {
        std::cout << tempQueue.front() << " ";
        tempQueue.pop();
    }
    std::cout << std::endl;

    // Simulating people leaving the queue in the order they joined
    while (!ticketQueue.empty()) {
        std::cout << ticketQueue.front() << " got their ticket and left the queue." << std::endl;
        ticketQueue.pop();
    }

    std::cout << "All people have received their tickets and the queue is now empty." << std::endl;

    return 0;
}
