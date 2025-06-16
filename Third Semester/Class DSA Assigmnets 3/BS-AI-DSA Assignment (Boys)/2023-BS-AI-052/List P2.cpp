#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;
struct Task {
    string name;
    string priority;

    Task(string n, string p) : name(n), priority(p) {}
};
bool compareTasks(const Task &a, const Task &b) {
    string priorities[] = {"high", "medium", "low"};
    int priorityA = find(begin(priorities), end(priorities), a.priority) - begin(priorities);
    int priorityB = find(begin(priorities), end(priorities), b.priority) - begin(priorities);
    return priorityA < priorityB; 
}

int main() {
    list<Task> taskList; 
    string choice, taskName, priority;

    while (true) {
        cout << "\nEnter your choice (add/remove/display/exit): ";
        cin >> choice;

        if (choice == "add") {
            cout << "Enter task name: ";
            cin.ignore(); 
            getline(cin, taskName);

            cout << "Enter task priority (high/medium/low): ";
            cin >> priority;

            if (priority == "high" || priority == "medium" || priority == "low") {
                taskList.push_back(Task(taskName, priority));
                cout << "Task added." << endl;
            } else {
                cout << "Invalid priority. Please enter high, medium, or low." << endl;
            }
        } 
        else if (choice == "remove") {
            cout << "Enter task name to remove: ";
            cin.ignore();
            getline(cin, taskName);

            // Find and remove the task from the list
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

                taskList.sort(compareTasks);
                cout << "Tasks in Priority Order: " << endl;
                for (const auto &task : taskList) {
                    cout << "Task: " << task.name << ", Priority: " << task.priority << endl;
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
