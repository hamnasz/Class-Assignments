#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() 
{
    list<pair<string, string>> taskList;
    string task, priority;
    int choice;

    while(true) {
        cout << "1. Add task\n2. Remove task\n3. Display tasks\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter task name: ";
                cin >> task;
                cout << "Enter priority (high, medium, low): ";
                cin >> priority;
                taskList.push_back(make_pair(task, priority));
                break;

            case 2:
                cout << "Enter task name to remove: ";
                cin >> task;
                taskList.remove_if([task](const pair<string, string>& t) { return t.first == task; });
                break;

            case 3:
                cout << "Current tasks:\n";
                for (const auto& t : taskList) 
                {
                    cout << "Task: " << t.first << ", Priority: " << t.second << endl;
                }
                break;

            case 4:
                cout << "Exiting program.\n";
                return 0;
                
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
