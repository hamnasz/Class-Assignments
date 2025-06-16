#include <iostream>
#include <string>

using namespace std;

enum Priority {
    HIGH,
    MEDIUM,
    LOW
};

struct Task {
    string description;
    Priority priority;
    Task* next;
};

class TaskList {
private:
    Task* head;

    // Helper function to get a string representation of the priority
    string priorityToString(Priority priority) const {
        switch (priority) {
            case HIGH: return "High";
            case MEDIUM: return "Medium";
            case LOW: return "Low";
            default: return "Unknown";
        }
    }

public:
    TaskList() : head(nullptr) {}

    // Add a task in the correct priority order
    void addTask(const string& description, Priority priority) {
        Task* newTask = new Task{description, priority, nullptr};

        // Insert at the beginning if head is empty or if new task has higher priority than head
        if (!head || priority < head->priority) {
            newTask->next = head;
            head = newTask;
        } else {
            // Insert in the correct position based on priority
            Task* current = head;
            while (current->next && current->next->priority <= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }

        cout << "Task \"" << description << "\" added with " << priorityToString(priority) << " priority.\n";
    }

    // Remove a task by description
    void removeTask(const string& description) {
        if (!head) {
            cout << "The task list is empty.\n";
            return;
        }

        // Check if the task to remove is the head
        if (head->description == description) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task \"" << description << "\" removed from the task list.\n";
            return;
        }

        // Search for the task in the list
        Task* current = head;
        while (current->next && current->next->description != description) {
            current = current->next;
        }

        if (current->next) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Task \"" << description << "\" removed from the task list.\n";
        } else {
            cout << "Task \"" << description << "\" not found in the task list.\n";
        }
    }

    // Display all tasks in priority order
    void displayTasks() const {
        if (!head) {
            cout << "The task list is empty.\n";
            return;
        }

        cout << "Current tasks in priority order:\n";
        Task* temp = head;
        while (temp) {
            cout << "- " << temp->description << " [" << priorityToString(temp->priority) << "]\n";
            temp = temp->next;
        }
    }

    // Destructor to clean up the list
    ~TaskList() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskList taskList;
    int choice;
    string description;
    int priorityInput;
    Priority priority;

    do {
        cout << "\nTask Management Menu:\n";
        cout << "1. Add task\n";
        cout << "2. Remove task\n";
        cout << "3. Display tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter priority (0 = High, 1 = Medium, 2 = Low): ";
                cin >> priorityInput;
                cin.ignore();
                
                if (priorityInput < 0 || priorityInput > 2) {
                    cout << "Invalid priority. Please enter 0, 1, or 2.\n";
                    break;
                }

                priority = static_cast<Priority>(priorityInput);
                taskList.addTask(description, priority);
                break;

            case 2:
                cout << "Enter task description to remove: ";
                getline(cin, description);
                taskList.removeTask(description);
                break;

            case 3:
                taskList.displayTasks();
                break;

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

