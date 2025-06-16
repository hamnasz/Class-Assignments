#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    string name;
    string priority;
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const string& name, const string& priority) {
        tasks.push_back({name, priority});
    }

    void removeTask(const string& name) {
        auto it = remove_if(tasks.begin(), tasks.end(), [&name](Task& t) { return t.name == name; });
        tasks.erase(it, tasks.end());
    }

    void displayTasks() {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority < b.priority;
        });
        for (const auto& task : tasks) {
            cout << task.name << " (" << task.priority << ")\n";
        }
    }
};

int main() {
    TaskManager manager;
    manager.addTask("Finish report", "high");
    manager.addTask("Email client", "medium");
    manager.displayTasks();
    manager.removeTask("Email client");
    manager.displayTasks();
    return 0;
}
