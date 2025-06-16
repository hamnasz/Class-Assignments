//task manager
#include <iostream>
#include <list>

using namespace std;

int main() {
    list<pair<int, string>> tasks;
    int choice;

    while (true) {
        cout << "1. Add task\n2. Remove task\n3. Display tasks\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                int priority;
                string task;
                cout << "Enter priority (1-3): ";
                cin >> priority;
                cout << "Enter task: ";
                cin >> task;
                tasks.push_back(make_pair(priority, task));
                tasks.sort(); // Sort tasks by priority
                break;
            }
            case 2: {
                if (tasks.empty()) {
                    cout << "No tasks to remove.\n";
                } else {
                    tasks.pop_front();
                    cout << "Highest priority task removed.\n";
                }
                break;
            }
            case 3: {
                if (tasks.empty()) {
                    cout << "No tasks to display.\n";
                } else {
                    cout << "Tasks:\n";
                    for (const auto& task : tasks) {
                        cout << "- Priority " << task.first << ": " << task.second << endl;
                    }
                }
                break;
            }
            case 4:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}