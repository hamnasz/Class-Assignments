#include <iostream>
#include <set>
using namespace std;

int main() {
    int arr[10], n;
    set<int> uniqueValues;
    
    cout << "Enter number of elements (max 10): ";
    cin >> n;
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        uniqueValues.insert(arr[i]);
    }
    
    cout << "Unique values: ";
    for (auto value : uniqueValues) {
        cout << value << " ";
    }
    cout << endl;
    return 0;
}