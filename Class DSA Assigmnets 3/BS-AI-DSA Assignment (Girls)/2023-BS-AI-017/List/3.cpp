#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100; // Maximum number of students

int main()
{
    string student[MAX_STUDENTS]; // Array to store student names
    int studentCount = 0;         // Current number of students
    string choice, name;

    while (true)
    {
        cout << "Enter your choice (add/remove/display/sort/exit): ";
        cin >> choice;

        if (choice == "add")
        {
            if (studentCount >= MAX_STUDENTS)
            {
                cout << "Cannot add more students. List is full." << endl;
                continue;
            }
            cout << "Enter name of student to add: ";
            cin >> name;
            student[studentCount] = name; // Add student to the array
            studentCount++;               // Increment student count
            cout << name << " added." << endl;
        }
        else if (choice == "remove")
        {
            cout << "Enter name of student to remove: ";
            cin >> name;
            bool found = false; // Flag to check if student is found

            for (int i = 0; i < studentCount; i++)
            {
                if (student[i] == name)
                {
                    found = true;
                    // Shift students left to remove the student
                    for (int j = i; j < studentCount - 1; j++)
                    {
                        student[j] = student[j + 1];
                    }
                    studentCount--; // Decrease student count
                    cout << name << " removed." << endl;
                    break;
                }
            }

            if (!found)
            {
                cout << name << " not found." << endl;
            }
        }
        else if (choice == "display")
        {
            cout << "Students list: ";
            for (int i = 0; i < studentCount; i++)
            {
                cout << student[i] << " ";
            }
            cout << endl;
        }
        else if (choice == "sort")
        {
            // Simple bubble sort implementation
            for (int i = 0; i < studentCount - 1; i++)
            {
                for (int j = 0; j < studentCount - i - 1; j++)
                {
                    if (student[j] > student[j + 1])
                    {
                        // Swap if out of order
                        string temp = student[j];
                        student[j] = student[j + 1];
                        student[j + 1] = temp;
                    }
                }
            }

            cout << "Sorted Students list: ";
            for (int i = 0; i < studentCount; i++)
            {
                cout << student[i] << " ";
            }
            cout << endl;
        }
        else if (choice == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}