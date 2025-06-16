#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int arr[10];
    vector<int> uniqueArr;
    cout << "Enter 10 integers: ";
    for(int i = 0; i < 10; i++) {
        cin >> arr[i];
        if(find(uniqueArr.begin(), uniqueArr.end(), arr[i]) == uniqueArr.end()) {
            uniqueArr.push_back(arr[i]);
        }
    }
    cout << "Array without duplicates: ";
    for(int val : uniqueArr) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
