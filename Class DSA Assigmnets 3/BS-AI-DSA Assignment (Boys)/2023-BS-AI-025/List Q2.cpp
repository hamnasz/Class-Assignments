#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;
struct Task {
    string name;
    int priority; 
    Task(string n, int p) : name(n), priority(p) {}
};

int main() {
    list<Task> taskList; 
    string choice, taskName;
    int priority;
    while (true) {
        cout << "\nEnter your choice (add/remove/display/exit): ";
        cin >> choice;
        if (choice == "add") {
            cout << "Enter task name: ";
            cin>>taksName
            cout << "Enter task priority (1 for high, 2 for medium, 3 for low): ";
            cin >> priority;
            if (priority >= 1 && priority <= 3) {
                taskList.push_back(Task(taskName, priority));
                cout << "Task added." << endl;
            } else {
                cout << "Invalid priority. Please enter 1 (high), 2 (medium), or 3 (low)." << endl;
            }
        } 
        else if (choice == "remove") {
            cout << "Enter task name to remove: ";
            cin.ignore();
            getline(cin, taskName);
            auto it = find_if(taskList.begin(), taskList.end(), [&](const Task &t) {
                return t.name == taskName;
            });

            if (it != taskList.end()) {
                taskList.erase(it);
                cout << "Task removed." << endl;
            } else {
                cout << "Task not found." << endl;
            }
        } 
        else if (choice == "display") {
            if (!taskList.empty()) {
                taskList.sort([](const Task &a, const Task &b) {
                    return a.priority < b.priority; // Sort by priority
                });
                cout << "Tasks in Priority Order: " << endl;
                for (const auto &task : taskList) {
                    cout << "Task: " << task.name << ", Priority: ";
                    if (task.priority == 1) {
                        cout << "High";
                    } else if (task.priority == 2) {
                        cout << "Medium";
                    } else {
                        cout << "Low";
                    }
                    cout << endl;
                }
            } else {
                cout << "No tasks to display." << endl;
            }
        } 
        else if (choice == "exit") {
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
