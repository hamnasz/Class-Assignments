#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> studentList;
    
    while (true) {
        cout << "Student list: ";
        for (auto student : studentList) {
            cout << student << " ";
        }
        cout << endl;
        cout << "1. Add student\n2. Remove student\n3. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string student;
            cout << "Enter student name to add: ";
            cin >> student;
            studentList.push_back(student);
            studentList.sort();
        } else if (choice == 2) {
            string student;
            cout << "Enter student name to remove: ";
            cin >> student;
            studentList.remove(student);
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}