#include <iostream>
#include <string>
#include <list>
using namespace std;

struct Task {
    string description;
    string priority;
};

class TaskManager {
private:
    list<Task> tasks;

    static bool compareTasks(const Task &a, const Task &b) {
        if (a.priority == "high" && (b.priority == "medium" || b.priority == "low")) return true;
        if (a.priority == "medium" && b.priority == "low") return true;
        return false;
    }

public:
    void addTask(const string &description, const string &priority) {
        tasks.push_back({description, priority});
        tasks.sort(compareTasks);
    }

    void removeTask(const string &description) {
        tasks.remove_if([&description](const Task &task) { return task.description == description; });
    }

    void displayTasks() const {
        for (const auto &task : tasks) {
            cout << task.description << " (" << task.priority << ")\n";
        }
    }
};

int main() {
    TaskManager manager;
    int choice;
    string description, priority;

    do {
        cout << "1. Add task\n2. Remove task\n3. Display tasks\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter task priority (high, medium, low): ";
                cin >> priority;
                manager.addTask(description, priority);
                break;
            case 2:
                cout << "Enter task description to remove: ";
                cin.ignore();
                getline(cin, description);
                manager.removeTask(description);
                break;
            case 3:
                manager.displayTasks();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
