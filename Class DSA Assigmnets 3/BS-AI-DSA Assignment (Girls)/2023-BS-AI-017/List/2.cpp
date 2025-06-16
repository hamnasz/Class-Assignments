#include <iostream>
#include <string>
using namespace std;

struct Task
{
    string name;
    int priority;
    Task(string n, int p) : name(n), priority(p) {}
};

int main()
{
    Task taskList[10]; // Array to hold up to 10 tasks
    int taskCount = 0; // Current number of tasks
    string choice, taskName;
    int priority;

    while (true)
    {
        cout << "\nEnter your choice (add/remove/display/exit): ";
        cin >> choice;

        if (choice == "add")
        {
            if (taskCount >= 10)
            {
                cout << "Task list is full. Cannot add more tasks." << endl;
                continue;
            }
            cout << "Enter task name: ";
            cin >> taskName;
            cout << "Enter task priority (1 for high, 2 for medium, 3 for low): ";
            cin >> priority;

            if (priority >= 1 && priority <= 3)
            {
                taskList[taskCount] = Task(taskName, priority);
                taskCount++;
                cout << "Task added." << endl;
            }
            else
            {
                cout << "Invalid priority. Please enter 1, 2, or 3." << endl;
            }
        }
        else if (choice == "remove")
        {
            cout << "Enter task name to remove: ";
            cin.ignore(); // Clear the input buffer
            getline(cin, taskName);

            bool found = false; // Flag to check if task is found
            for (int i = 0; i < taskCount; i++)
            {
                if (taskList[i].name == taskName)
                {
                    found = true;
                    // Shift tasks left to remove the task
                    for (int j = i; j < taskCount - 1; j++)
                    {
                        taskList[j] = taskList[j + 1];
                    }
                    taskCount--; // Decrease task count
                    cout << "Task removed." << endl;
                    break;
                }
            }

            if (!found)
            {
                cout << "Task not found." << endl;
            }
        }
        else if (choice == "display")
        {
            if (taskCount == 0)
            {
                cout << "No tasks to display." << endl;
            }
            else
            {
                cout << "Tasks in Order: " << endl;
                for (int i = 0; i < taskCount; i++)
                {
                    cout << "Task: " << taskList[i].name << ", Priority: ";
                    if (taskList[i].priority == 1)
                    {
                        cout << "High";
                    }
                    else if (taskList[i].priority == 2)
                    {
                        cout << "Medium";
                    }
                    else
                    {
                        cout << "Low";
                    }
                    cout << endl;
                }
            }
        }
        else if (choice == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
