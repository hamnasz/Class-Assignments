#include <iostream>
using namespace std;

int main() {
    // Array of grades
    char grades[5] = {'A', 'B', 'C', 'B', 'A'};
    
    cout << "Student Grades:" << endl;
    
    // Loop through the array and display each grade
    for (int i = 0; i < 5; i++) {
        cout << "Student " << i + 1 << ": " << grades[i] << endl;
    }

    return 0;
}
