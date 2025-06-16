#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    list<string> students = {"Alice", "Bob"};
    students.sort();

    cout << "Student Roll Call: ";
    for (const string& student : students) {
        cout << student << " ";
    }
    cout << endl;
    return 0;
}
