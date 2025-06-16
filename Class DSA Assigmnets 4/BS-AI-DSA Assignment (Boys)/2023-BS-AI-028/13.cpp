#include <iostream>
#include <list>
#include <string>
using namespace std;

void addStudent(list<string>& students, string name) {
    students.push_back(name);
    students.sort();
}

void removeStudent(list<string>& students, string name) {
    students.remove(name);
}

void displayStudents(list<string>& students) {
    for (string name : students) {
        cout << name << endl;
    }
}

int main() {
    list<string> students;
    addStudent(students, "Alice");
    addStudent(students, "Bob");
    addStudent(students, "Charlie");
    displayStudents(students);
    removeStudent(students, "Bob");
    displayStudents(students);
    return 0;
}
