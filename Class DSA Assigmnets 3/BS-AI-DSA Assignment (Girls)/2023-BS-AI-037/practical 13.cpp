#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class StudentList {
private:
    std::vector<std::string> students;

public:
    // Add a student name to the list
    void addStudent(const std::string& name) {
        students.push_back(name);
        std::sort(students.begin(), students.end());
        std::cout << "Added: " << name << std::endl;
    }

    // Remove a student name from the list
    void removeStudent(const std::string& name) {
        auto it = std::find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            std::cout << "Removed: " << name << std::endl;
        } else {
            std::cout << "Student not found." << std::endl;
        }
    }

    // Display the list of student names in alphabetical order
    void displayStudents() const {
        if (students.empty()) {
            std::cout << "The student list is empty." << std::endl;
            return;
        }

        std::cout << "Student List:" << std::endl;
        for (const auto& student : students) {
            std::cout << "- " << student << std::endl;
        }
    }
};

int main() {
    StudentList studentList;
    int choice;
    std::string name;

    do {
        std::cout << "\n1. Add student\n2. Remove student\n3. Display students\n4. Exit\nChoose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter student name to add: ";
                std::getline(std::cin, name);
                studentList.addStudent(name);
                break;
            case 2:
                std::cout << "Enter student name to remove: ";
                std::getline(std::cin, name);
                studentList.removeStudent(name);
                break;
            case 3:
                studentList.displayStudents();
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
