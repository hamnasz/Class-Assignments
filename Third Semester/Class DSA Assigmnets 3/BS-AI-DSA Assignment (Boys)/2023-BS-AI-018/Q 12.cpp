#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Enum for task priority
enum class Priority { High, Medium, Low };

// Struct to represent a task
struct Task {
    string description;
    Priority priority;
};

// Function to display tasks
void displayTasks(const vector<Task>& tasks) {
    cout << "Tasks:\n";
    for (const auto& task : tasks) {
        cout << "Priority: ";
        switch (task.priority) {
            case Priority::High:
                cout << "High";
                break;
            case Priority::Medium:
                cout << "Medium";
                break;
            case Priority::Low:
                cout << "Low";
                break;
        }
        cout << ", Description: " << task.description << "\n";
    }
}

// Function to add a task
void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    cout << "Enter task priority (1 - High, 2 - Medium, 3 - Low): ";
    int priority;
    cin >> priority;
    cin.ignore(); // Ignore newline character left in input buffer
    switch (priority) {
        case 1:
            newTask.priority = Priority::High;
            break;
        case 2:
            newTask.priority = Priority::Medium;
            break;
        case 3:
            newTask.priority = Priority::Low;
            break;
        default:
            cout << "Invalid priority. Defaulting to Medium.\n";
            newTask.priority = Priority::Medium;
            break;
    }
    tasks.push_back(newTask);
}

// Function to remove a task
void removeTask(vector<Task>& tasks) {
    int taskNumber;
    displayTasks(tasks);
    cout << "Enter task number to remove (1-" << tasks.size() << "): ";
    cin >> taskNumber;
    cin.ignore(); // Ignore newline character left in input buffer
    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        tasks.erase(tasks.begin() + taskNumber - 1);
    } else {
        cout << "Invalid task number.\n";
    }
}

// Custom comparator for sorting tasks by priority
bool compareTasks(const Task& a, const Task& b) {
    return static_cast<int>(a.priority) > static_cast<int>(b.priority);
}

int main() {
    vector<Task> tasks;

    while (true) {
        cout << "\nTask Manager\n";
        cout << "1. Display tasks\n";
        cout << "2. Add task\n";
        cout << "3. Remove task\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        int option;
        cin >> option;
        cin.ignore(); // Ignore newline character left in input buffer

        switch (option) {
            case 1:
                sort(tasks.begin(), tasks.end(), compareTasks);
                displayTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                removeTask(tasks);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }

    return 0;
}
