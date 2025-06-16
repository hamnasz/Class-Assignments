// Simulate a basic ticket queue, where people enter and leave the line in the order they joined

#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Function to display the elements of the queue
void display(queue<string> q) 
{
    cout << "Queue: ";
    while (!q.empty())
    {
        cout << q.front() << " "; // Print the front element of the queue
        q.pop(); // Remove the front element from the queue
    }
    cout << endl;
}

int main() 
{
    queue<string> ticketQueue;
    int choice;
    string name;

    // Start an infinite loop to display the menu and process user choices
    while (true)
    {
        // Display menu options
        cout << "\nTicket Queue System\n";
        cout << "1. Join the queue\n";
        cout << "2. Serve the next person\n";
        cout << "3. Display queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Read user choice

        // Switch statement to handle user choices
        switch (choice) 
        {
            // Join the queue
            case 1: 
                cout << "Enter name: ";
                cin >> name;
                ticketQueue.push(name); // Add the name to the queue
                cout << name << " has joined the Queue.\n";
                break;

            // Serve the next person in the queue
            case 2: 
                if (!ticketQueue.empty())
                {
                    cout << ticketQueue.front() << " has left the Queue\n";
                    ticketQueue.pop(); // Remove the served person from the queue
                } 
                else 
                {
                    cout << "The queue is empty.\n";
                }
                break;

            // Display the current state of the queue
            case 3:
                if (ticketQueue.empty())
                {
                    cout << "The queue is empty.\n"; // Inform that the queue is empty
                } 
                else 
                {
                    display(ticketQueue); // Call the display function to show the queue
                }
                break;

            // Exit the program
            case 4: 
                cout << "Exiting the program.\n";
                return 0;

            // Handle invalid choices
            default: 
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } 

    return 0;
}
