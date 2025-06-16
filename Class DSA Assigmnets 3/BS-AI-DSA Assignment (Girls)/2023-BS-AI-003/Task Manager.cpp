#include <iostream>
#include <string>
using namespace std;
struct Task {
    string description;
    string priority;
    Task* next;
};
class TaskList {
private:
    Task* head;
    int getPriorityValue(const string& priority) {
        if (priority == "high") return 1;
        if (priority == "medium") return 2;
        return 3; 
    }

public:
    TaskList() : head(nullptr) {}
    void addTask(const string& description, const string& priority) {
        Task* newTask = new Task{description, priority, nullptr};
        if (!head || getPriorityValue(priority) < getPriorityValue(head->priority)) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next && getPriorityValue(priority) >= getPriorityValue(temp->next->priority)) {
                temp = temp->next;
            }
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task \"" << description << "\" with " << priority << " priority added." << endl;
    }
    void removeTask(const string& description) {
        Task* temp = head;
        Task* prev = nullptr;

        while (temp && temp->description != description) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Task \"" << description << "\" not found." << endl;
            return;
        }

        if (prev) {
            prev->next = temp->next;
        } else {
            head = temp->next;
        }
        delete temp;
        cout << "Task \"" << description << "\" removed." << endl;
    }
    void displayTasks() const {
        if (!head) {
            cout << "No tasks in the list." << endl;
            return;
        }

        Task* temp = head;
        cout << "Task List:" << endl;
        while (temp) {
            cout << "- " << temp->description << " [" << temp->priority << "]" << endl;
            temp = temp->next;
        }
    }
    ~TaskList() {
        Task* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskList tasks;
    string command, description, priority;

    while (true) {
        cout << "\nEnter command (add/remove/display/exit): ";
        cin >> command;

        if (command == "add") {
            cin.ignore(); // clear the newline
            cout << "Enter task description: ";
            getline(cin, description);
            cout << "Enter priority (high/medium/low): ";
            cin >> priority;
            if (priority == "high" || priority == "medium" || priority == "low") {
                tasks.addTask(description, priority);
            } else {
                cout << "Invalid priority. Please use high, medium, or low." << endl;
            }
        } 
        else if (command == "remove") {
            cin.ignore(); // clear the newline
            cout << "Enter task description to remove: ";
            getline(cin, description);
            tasks.removeTask(description);
        } 
        else if (command == "display") {
            tasks.displayTasks();
        } 
        else if (command == "exit") {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please enter 'add', 'remove', 'display', or 'exit'." << endl;
        }
    }

    return 0;
}