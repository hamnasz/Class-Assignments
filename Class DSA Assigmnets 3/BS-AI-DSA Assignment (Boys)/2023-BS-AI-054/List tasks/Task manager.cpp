#include <iostream>
#include <string>
using namespace std;

struct Task {
    string description;
    string priority;
    Task* next;
};

// Add a task to the list
void addTask(Task*& head, const string& desc, const string& prio) {
    Task* newTask = new Task{desc, prio, nullptr};
    Task* current = head;
    Task* prev = nullptr;

    // Insert based on priority
    while (current && current->priority <= prio) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr) {
        newTask->next = head;
        head = newTask;
    } else {
        prev->next = newTask;
        newTask->next = current;
    }

    cout << "Added: " << desc << " [" << prio << "]\n";
}

// Remove a task by description
void removeTask(Task*& head, const string& desc) {
    Task* current = head;
    Task* prev = nullptr;

    while (current && current->description != desc) {
        prev = current;
        current = current->next;
    }

    if (current) {
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << "Removed: " << desc << "\n";
    } else {
        cout << desc << " not found.\n";
    }
}

// Display all tasks
void displayTasks(Task* head) {
    if (!head) {
        cout << "No tasks in the list.\n";
        return;
    }
    cout << "Tasks:\n";
    for (Task* current = head; current; current = current->next) {
        cout << "- " << current->description << " [" << current->priority << "]\n";
    }
}

int main() {
    Task* taskList = nullptr;
    string command, description, priority;

    while (true) {
        cout << "\nCommand (add, remove, display, exit): ";
        cin >> command;

        if (command == "add") {
            cout << "Description: ";
            cin.ignore();
            getline(cin, description);
            cout << "Priority (high, medium, low): ";
            cin >> priority;
            addTask(taskList, description, priority);
        } 
        else if (command == "remove") {
            cout << "Description to remove: ";
            cin.ignore();
            getline(cin, description);
            removeTask(taskList, description);
        } 
        else if (command == "display") {
            displayTasks(taskList);
        } 
        else if (command == "exit") {
            cout << "Exiting...\n";
            break;
        } 
        else {
            cout << "Invalid command.\n";
        }
    }

    // Clean up memory
    while (taskList) {
        Task* temp = taskList;
        taskList = taskList->next;
        delete temp;
    }

    return 0;
}
