#include <iostream>
#include <list>
#include <string>
using namespace std;


void takeTicket(list<int>& Ticket, int& ticketNumber) 
{
    Ticket.push_back(ticketNumber);
    cout << "Ticket " << ticketNumber << " taken." << endl;
    ticketNumber++;
    cout<<endl;
}


void serveTicket(list<int>& Ticket) 
{
    if (Ticket.empty()) 
    {
        cout << "No tickets to serve." << endl;
    } 
    else 
    {
        int servedTicket = Ticket.front();
        Ticket.pop_front(); 
        cout << "Serving ticket " << servedTicket << "." << endl;
        cout<<endl;
    }
}
void displayQueue(list<int>& Ticket)
{
    if (Ticket.empty()) 
    {
        cout << "The queue is empty." << endl;
        cout<<endl;
        return;
    }

    cout << "Current queue: ";
    for (int ticket : Ticket) 
    {
        cout << ticket << " ";
    }
    cout << endl; 
}

int main() 
{
    list<int> Ticket;
    int ticketNumber = 1;
    int choice;

    while(true)
    {
        cout << "Ticketing System Menu:\n";
        cout << "1. Take a Ticket\n";
        cout << "2. Serve a Ticket\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                takeTicket(Ticket, ticketNumber);
                break;

            case 2:
                serveTicket(Ticket);
                break;

            case 3:
                displayQueue(Ticket);
                break;

            case 4:
                cout << "Exiting the system." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
