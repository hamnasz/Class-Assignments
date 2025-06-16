#include <iostream>
#include <string>
using namespace std;

// Node structure for the linked list
struct Task {
    string name;
    string priority; // "high", "medium", or "low"
    Task* next;
};

// Class for managing the task list
class TaskList {
private:
    Task* head;

public:
    TaskList() : head(nullptr) {}

    // Function to add a task
    void addTask(const string& name, const string& priority) {
        Task* newTask = new Task{name, priority, nullptr};

        // Insert the task in priority order
        if (!head || priorityOrder(priority) < priorityOrder(head->priority)) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next && priorityOrder(priority) >= priorityOrder(current->next->priority)) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }

        cout << "Task '" << name << "' with priority '" << priority << "' added." << endl;
    }

    // Function to remove a task
    void removeTask(const string& name) {
        if (!head) {
            cout << "No tasks to remove." << endl;
            return;
        }

        Task* current = head;
        Task* prev = nullptr;

        // Search for the task to remove
        while (current && current->name != name) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cout << "Task '" << name << "' not found." << endl;
            return;
        }

        // Task found; remove it from the list
        if (prev) {
            prev->next = current->next;
        } else {
            head = current->next; // Remove the head task
        }

        delete current; // Free memory
        cout << "Task '" << name << "' removed." << endl;
    }

    // Function to display tasks
    void displayTasks() const {
        if (!head) {
            cout << "No tasks available." << endl;
            return;
        }

        cout << "Current Task List (in priority order):" << endl;
        Task* current = head;
        while (current) {
            cout << "- [" << current->priority << "] " << current->name << endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~TaskList() {
        Task* current = head;
        while (current) {
            Task* nextTask = current->next;
            delete current;
            current = nextTask;
        }
    }

private:
    // Helper function to determine the priority order
    int priorityOrder(const string& priority) const {
        if (priority == "high") return 1;
        if (priority == "medium") return 2;
        if (priority == "low") return 3;
        return 4; // Default for invalid priority
    }
};

int main() {
    TaskList taskList;
    int choice;
    string name, priority;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Display Tasks\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                cout << "Enter task name: ";
                getline(cin, name);
                cout << "Enter priority (high, medium, low): ";
                getline(cin, priority);
                taskList.addTask(name, priority);
                break;
            case 2:
                cout << "Enter task name to remove: ";
                getline(cin, name);
                taskList.removeTask(name);
                break;
            case 3:
                taskList.displayTasks();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
