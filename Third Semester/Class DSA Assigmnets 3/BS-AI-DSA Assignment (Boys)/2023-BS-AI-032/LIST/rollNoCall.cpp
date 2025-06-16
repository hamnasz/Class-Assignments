#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class StudentRollCall {
private:
    vector<string> students;

public:
    void addStudent(const string& name) {
        students.push_back(name);
    }

    void removeStudent(const string& name) {
        auto it = remove(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
        } else {
            cout << "Student not found.\n";
        }
    }

    void displayStudents() {
        sort(students.begin(), students.end());
        for (const auto& student : students) {
            cout << student << endl;
        }
    }
};

int main() {
    StudentRollCall rollCall;
    rollCall.addStudent("A");
    rollCall.addStudent("B");
    rollCall.addStudent("C");
    rollCall.displayStudents();
    rollCall.removeStudent("B");
    rollCall.displayStudents();
    return 0;
}
