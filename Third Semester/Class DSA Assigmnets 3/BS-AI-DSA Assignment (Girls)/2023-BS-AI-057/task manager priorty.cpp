#include <iostream>
#include <list>
using namespace std;

struct Task {
    string name;
    string priority;
};

bool compareTasks(const Task &a, const Task &b) {
    if (a.priority == "high" && b.priority != "high") return true;
    if (a.priority == "medium" && b.priority == "low") return true;
    return false;
}

int main() {
    list<Task> taskList;
    Task task;
    int choice;

    do {
        cout << "1. Add Task\n2. Remove Task\n3. Display Tasks\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter task name: ";
            cin >> task.name;
            cout << "Enter priority (high, medium, low): ";
            cin >> task.priority;
            taskList.push_back(task);
            taskList.sort(compareTasks);
        } else if (choice == 2) {
            cout << "Enter task name to remove: ";
            cin >> task.name;
            taskList.remove_if([task](const Task &t) { return t.name == task.name; });
        } else if (choice == 3) {
            cout << "Task List:\n";
            for (const Task &t : taskList) {
                cout << t.name << " (" << t.priority << ")" << endl;
            }
        }
    } while (choice != 4);

    return 0;
}
