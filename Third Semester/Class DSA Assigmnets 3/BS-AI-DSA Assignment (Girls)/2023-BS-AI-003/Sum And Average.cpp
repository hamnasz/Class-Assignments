#include <iostream>
using namespace std;
int main() 
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;
    for (int i = 0; i < 10; i++) {
       sum += array[i];
    }
    double average = (double)sum / 10;
    cout << "Array elements: ";
    for (int i = 0; i < 10; i++) {
    cout << array[i] << " ";
    }
    cout <<endl;
    cout << "Sum: " << sum <<endl;
    cout << "Average: " << average <<endl;
    return 0;
}
