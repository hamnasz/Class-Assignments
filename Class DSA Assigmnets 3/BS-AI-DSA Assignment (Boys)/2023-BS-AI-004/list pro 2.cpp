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
    list<Task> tasks;
    int choice;
    Task task;

    do {
        cout << "1. Add task\n2. Remove task\n3. Show tasks\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter task name and priority (high, medium, low): ";
            cin >> task.name >> task.priority;
            tasks.push_back(task);
            tasks.sort(compareTasks);
        } else if (choice == 2) {
            cout << "Enter task name to remove: ";
            cin >> task.name;
            tasks.remove_if([&task](const Task &t) { return t.name == task.name; });
        } else if (choice == 3) {
            for (const Task &t : tasks) cout << t.name << " [" << t.priority << "]\n";
        }
    } while (choice != 4);
    return 0;
}
