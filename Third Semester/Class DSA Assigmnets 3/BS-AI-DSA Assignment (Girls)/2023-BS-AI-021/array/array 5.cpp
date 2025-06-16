#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main() {
    const int size = 10; 
    int numbers[size];

    cout << "Enter " << size << " integers:" <<endl;
    for (int i = 0; i < size; ++i) {
        cin >> numbers[i];
    }

    std::set<int> uniqueValues;

    for (int i = 0; i < size; ++i) {
        uniqueValues.insert(numbers[i]);
    }

    cout << "Unique values:" <<endl;
    for (const int& value : uniqueValues) {
        cout << value << " ";
    }
    cout <<endl;

    return 0;
}