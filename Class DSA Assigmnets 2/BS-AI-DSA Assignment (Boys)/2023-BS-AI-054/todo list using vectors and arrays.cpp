#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int maxTasks = 5;
    string tasks[maxTasks];
    vector<bool> taskStatus;
    int taskCount = 0;
    char choice;

    do {
        if (taskCount < maxTasks) {
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, tasks[taskCount]);
            taskStatus.push_back(false);
            taskCount++;
            cout << "Task added successfully!" << endl;
        } else {
            cout << "Task list is full!" << endl;
        }
        
        cout << "Do you want to add another task? (y/n): ";
        cin >> choice;
    } while (choice == 'y' && taskCount < maxTasks);

    cout << "\nTo-Do List:" << endl;
    for (int i = 0; i < taskCount; i++) {
        cout << i + 1 << ". " << tasks[i] << " [";
        if (taskStatus[i]) {
            cout << "Completed";
        } else {
            cout << "Not Completed";
        }
        cout << "]" << endl;
    }

    return 0;
}
