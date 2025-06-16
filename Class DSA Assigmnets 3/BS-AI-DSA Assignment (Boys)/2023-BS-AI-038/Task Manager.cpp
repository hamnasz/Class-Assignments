#include <iostream>
#include <list>
#include <string>
using namespace std;

struct Task {
    string description;
    string priority;
};

int main() {
    list<Task> taskList;
    
    while (true) {
        cout << "Task list: ";
        for (auto task : taskList) {
            cout << task.description << " (" << task.priority << ") ";
        }
        cout << endl;
        cout << "1. Add task\n2. Remove task\n3. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            Task task;
            cout << "Enter task description: ";
            cin >> task.description;
            cout << "Enter task priority (high, medium, low): ";
            cin >> task.priority;
            taskList.push_back(task);
            taskList.sort([](const Task &a, const Task &b) {
                if (a.priority == "high" && b.priority != "high") return true;
                if (a.priority == "medium" && b.priority != "medium") return true;
                return a.description < b.description;
            });
        } else if (choice == 2) {
            string description;
            cout << "Enter task description to remove: ";
            cin >> description;
            taskList.remove_if([description](const Task &task) {
                return task.description == description;
            });
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}