#include <iostream>
using namespace std;
int main() {
    // Declare and initialize a 3x2 array to store marks for 3 students in 2 subjects
    int marks[3][2] = {
        {85, 90},  // Marks for Student 1 in Subject 1 and Subject 2
        {78, 82},  // Marks for Student 2 in Subject 1 and Subject 2
        {92, 88}   // Marks for Student 3 in Subject 1 and Subject 2
    };
    // Display the marks
    for (int i = 0; i < 3; i++) {
        cout << "Student " << i+1 << " Marks: ";
        for (int j = 0; j < 2; j++) {
            cout << marks[i][j] << " ";  // Print each student's marks
        }
        cout << endl;
    }
    return 0;
}
