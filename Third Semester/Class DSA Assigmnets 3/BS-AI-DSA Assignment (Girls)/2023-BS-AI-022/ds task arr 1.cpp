#include <iostream>
using namespace std;
int main()
 {
    int arr[10];  
    int sum = 0;  
    float average; 

    cout << "Enter 10 integers: ";
    for (int i = 0; i < 10; i++)
	{
        cin >> arr[i];
        sum += arr[i];  
    }

    average = sum / 10.0;

    cout << "Sum = " << sum << endl;
    cout << "Average = " << average << endl;

    return 0;
}
