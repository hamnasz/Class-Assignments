#include <iostream>
#include <string>

struct Task {
    std::string description;
    std::string priority; // high, medium, low
    Task* next;
};

class TaskManager {
private:
    Task* head = nullptr;

    // Helper function to get priority value for sorting
    int getPriorityValue(const std::string& priority) {
        if (priority == "high") return 1;
        if (priority == "medium") return 2;
        return 3; // low
    }

public:
    // Add a task in the correct priority order
    void addTask(const std::string& description, const std::string& priority) {
        Task* newTask = new Task{description, priority, nullptr};
        if (!head || getPriorityValue(priority) < getPriorityValue(head->priority)) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next && getPriorityValue(priority) >= getPriorityValue(current->next->priority)) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        std::cout << "Task added: " << description << " [" << priority << "]" << std::endl;
    }

    // Remove a task by description
    void removeTask(const std::string& description) {
        if (!head) {
            std::cout << "No tasks to remove." << std::endl;
            return;
        }

        if (head->description == description) {
            Task* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Task removed: " << description << std::endl;
            return;
        }

        Task* current = head;
        while (current->next && current->next->description != description) {
            current = current->next;
        }

        if (current->next) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            std::cout << "Task removed: " << description << std::endl;
        } else {
            std::cout << "Task not found." << std::endl;
        }
    }

    // Display all tasks in the list
    void displayTasks() const {
        if (!head) {
            std::cout << "No tasks in the list." << std::endl;
            return;
        }

        std::cout << "Tasks:" << std::endl;
        Task* current = head;
        while (current) {
            std::cout << "- " << current->description << " [" << current->priority << "]" << std::endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~TaskManager() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskManager taskManager;
    int choice;
    std::string description, priority;

    do {
        std::cout << "\n1. Add task\n2. Remove task\n3. Display tasks\n4. Exit\nChoose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                std::cout << "Enter priority (high, medium, low): ";
                std::getline(std::cin, priority);
                taskManager.addTask(description, priority);
                break;
            case 2:
                std::cout << "Enter task description to remove: ";
                std::getline(std::cin, description);
                taskManager.removeTask(description);
                break;
            case 3:
                taskManager.displayTasks();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
