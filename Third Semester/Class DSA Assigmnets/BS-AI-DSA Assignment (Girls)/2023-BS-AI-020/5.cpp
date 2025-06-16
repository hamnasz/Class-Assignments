#include <iostream>
using namespace std;

int main() {
    int marks[5], total = 0;

    for (int i = 0; i < 5; i++) {
        cout << "Enter marks for student " << i + 1 << ": ";
        cin >> marks[i];
        total += marks[i]; 
    }

    cout << "\nMarks of students: ";
    for (int i = 0; i < 5; i++) {
        cout << marks[i] << " ";
    }

    cout << "\nAverage marks: " << total / 5.0 << endl;

    return 0;
}
