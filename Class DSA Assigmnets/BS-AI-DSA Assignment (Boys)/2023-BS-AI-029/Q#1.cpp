#include <iostream>
using namespace std;

struct Student {
    string name;
    int age;
};

int main() {
    Student students[2] = {
        {"javed", 20},
        {"ali", 22}
    };

    cout << "Student Information:\n";
    for (int i = 0; i < 2; i++) {
        cout << "Name: " << students[i].name << ", Age: " << students[i].age << endl;
    }

    return 0;
}