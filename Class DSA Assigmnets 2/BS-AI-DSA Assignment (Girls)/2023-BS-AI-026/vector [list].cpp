#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers; 
    int n, element;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> element;
        numbers.push_back(element); 
    }

   
    cout << "List of elements:" << endl;
    for (int i = 0; i < numbers.size(); i++)
        cout << numbers[i] << " ";  
    cout << endl;

    return 0;
}
