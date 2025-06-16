#include <iostream>
#include <list>
#include <string>
using namespace std;

struct Task {
    string name;
    string priority;
};

bool compareTasks(Task a, Task b) {
    if (a.priority == "high") return true;
    if (a.priority == "medium" && b.priority != "high") return true;
    if (a.priority == "low" && b.priority == "low") return true;
    return false;
}

void addTask(list<Task>& tasks, string name, string priority) {
    Task newTask = {name, priority};
    tasks.push_back(newTask);
    tasks.sort(compareTasks);
}

void removeTask(list<Task>& tasks, string name) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->name == name) {
            tasks.erase(it);
            break;
        }
    }
}

void displayTasks(list<Task>& tasks) {
    for (auto task : tasks) {
        cout << task.name << " (" << task.priority << ")" << endl;
    }
}

int main() {
    list<Task> tasks;
    addTask(tasks, "Complete project", "high");
    addTask(tasks, "Clean room", "low");
    addTask(tasks, "Study", "medium");
    displayTasks(tasks);
    removeTask(tasks, "Clean room");
    displayTasks(tasks);
    return 0;
}
