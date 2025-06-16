#include <iostream>
using namespace std;

struct Student {
    string name;
    int age;
};

int main() {
    Student students[3] = {
        {"Zubair", 20},
        {"khan", 21},
        {"Hassan", 21}
    };

    cout << "Student Information:\n";
    for (int i = 0; i < 3; i++) {
        cout << "Name: " << students[i].name << ", Age: " << students[i].age << endl;
    }

    return 0;
}