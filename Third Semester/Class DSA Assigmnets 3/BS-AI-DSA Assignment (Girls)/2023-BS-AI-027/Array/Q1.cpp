#include <iostream>
using namespace std;

int main() 
{
    int arr[5]; 
    int Sum = 0;
    float Average;

    // Input elements
    cout << "Enter 5 elements:" << endl;
    for(int i = 0; i < 5; i++)
	 {
        cin >> arr[i];
        Sum += arr[i]; 
    }

    // Calculating average
    Average = Sum / 10.0;

    // Display sum and average
    cout << "Sum is: " << Sum << endl;
    cout << "Average is: " << Average << endl;

return 0;
}
