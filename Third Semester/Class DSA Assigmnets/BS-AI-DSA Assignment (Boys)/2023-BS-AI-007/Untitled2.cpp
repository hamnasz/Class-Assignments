#include <iostream>
using namespace std;
int main()
{
    string employees[] = {"Wahaaj\t= \t50000", "faisal\t= \t60000", "wishaq\t= \t55000", "hamna\t= \t62000", "yumna\t= \t58000"};
    cout << "Employee Names and Salaries" << endl;
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << employees[i] << "\n";
    }
    return 0;
}