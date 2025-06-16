#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() 
{
    vector<int> numbers = {1, 2, 3, 2, 4, 1, 5, 3};

    sort(numbers.begin(), numbers.end());
    auto last = unique(numbers.begin(), numbers.end());
    numbers.erase(last, numbers.end());

    cout << "Vector after removing duplicates: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}