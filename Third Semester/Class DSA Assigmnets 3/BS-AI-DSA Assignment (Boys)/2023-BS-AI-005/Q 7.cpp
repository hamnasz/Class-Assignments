#include <iostream>
#include <string>
using namespace std;

const int MAX_TASKS = 100;
string tasks[MAX_TASKS];  // Array to store task descriptions
string priorities[MAX_TASKS];  // Array to store task priorities
int taskCount = 0;  // Counter to keep track of the number of tasks

void addTask(const string& task, const string& priority) {
    if (taskCount < MAX_TASKS) {
        tasks[taskCount] = task;
        priorities[taskCount] = priority;
        taskCount++;
        cout << "Task \"" << task << "\" with priority \"" << priority << "\" added.\n";
    } else {
        cout << "Task list is full.\n";
    }
}

void removeTask(const string& task) {
    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i] == task) {
            found = true;
            // Shift tasks and priorities to the left to fill the gap
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
                priorities[j] = priorities[j + 1];
            }
            taskCount--;
            cout << "Task \"" << task << "\" removed.\n";
            break;
        }
    }
    if (!found) {
        cout << "Task \"" << task << "\" not found.\n";
    }
}

void displayTasks() {
    if (taskCount == 0) {
        cout << "No tasks to display.\n";
        return;
    }

    cout << "\nTasks (sorted by priority):\n";

    // Display high-priority tasks first
    for (int i = 0; i < taskCount; i++) {
        if (priorities[i] == "high") {
            cout << "- " << tasks[i] << " [High Priority]\n";
        }
    }
    // Display medium-priority tasks
    for (int i = 0; i < taskCount; i++) {
        if (priorities[i] == "medium") {
            cout << "- " << tasks[i] << " [Medium Priority]\n";
        }
    }
    // Display low-priority tasks
    for (int i = 0; i < taskCount; i++) {
        if (priorities[i] == "low") {
            cout << "- " << tasks[i] << " [Low Priority]\n";
        }
    }
}

int main() {
    int choice;
    string task, priority;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add task\n";
        cout << "2. Remove task\n";
        cout << "3. Display tasks\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, task);
                cout << "Enter priority (high, medium, low): ";
                getline(cin, priority);
                if (priority == "high" || priority == "medium" || priority == "low") {
                    addTask(task, priority);
                } else {
                    cout << "Invalid priority. Please enter 'high', 'medium', or 'low'.\n";
                }
                break;
            case 2:
                cout << "Enter task description to remove: ";
                getline(cin, task);
                removeTask(task);
                break;
            case 3:
                displayTasks();
                break;
            case 4:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid option. Please choose again.\n";
                break;
        }
    }
}