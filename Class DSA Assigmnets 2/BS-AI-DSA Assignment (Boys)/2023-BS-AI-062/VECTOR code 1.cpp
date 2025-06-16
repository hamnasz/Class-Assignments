#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() 
{
    vector<int> vec = {4, 2, 5, 1, 3};
    sort(vec.begin(), vec.end());

    cout << "Sorted vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout <<endl;
    return 0;
}