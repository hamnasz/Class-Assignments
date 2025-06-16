#include <iostream>
#include <string>

using namespace std;

enum class Priority {
    High,
    Medium,
    Low
};

struct TaskNode {
    string task;
    Priority priority;
    TaskNode* next;
};

class TaskManager {
private:
    TaskNode* head;

public:
    TaskManager() : head(nullptr) {}

    void addTask(const string& task, Priority priority) {
        TaskNode* newNode = new TaskNode();
        newNode->task = task;
        newNode->priority = priority;
        newNode->next = nullptr;

        if (head == nullptr || head->priority > priority) {
            newNode->next = head;
            head = newNode;
        } else {
            TaskNode* current = head;
            while (current->next != nullptr && current->next->priority <= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        cout << "Task \"" << task << "\" with priority " << (int)priority << " has been added." << endl;
    }

    void removeTask(const string& task) {
        TaskNode* current = head;
        TaskNode* previous = nullptr;

        while (current != nullptr) {
            if (current->task == task) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << "Task \"" << task << "\" has been removed." << endl;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Task \"" << task << "\" not found." << endl;
    }

    void displayTasks() const {
        if (head == nullptr) {
            cout << "No tasks in the list." << endl;
            return;
        }

        cout << "Tasks:" << endl;
        TaskNode* current = head;
        while (current != nullptr) {
            cout << "- " << current->task << " (Priority: " << (int)current->priority << ")" << endl;
            current = current->next;
        }
    }

    ~TaskManager() {
        TaskNode* current = head;
        while (current != nullptr) {
            TaskNode* next = current->next;
            delete current;
            current = next;
        }
    }
};

Priority stringToPriority(const string& priority) {
    if (priority == "high") {
        return Priority::High;
    } else if (priority == "medium") {
        return Priority::Medium;
    } else {
        return Priority::Low;
    }
}

int main() {
    TaskManager manager;
    int choice;
    string task, priority;

    do {
        cout << "\nTask Management Menu:" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. Display Tasks" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter task: ";
                getline(cin, task);
                cout << "Enter priority (high, medium, low): ";
                getline(cin, priority);
                manager.addTask(task, stringToPriority(priority));
                break;
            case 2:
                cout << "Enter task to remove: ";
                getline(cin, task);
                manager.removeTask(task);
                break;
            case 3:
                manager.displayTasks();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
