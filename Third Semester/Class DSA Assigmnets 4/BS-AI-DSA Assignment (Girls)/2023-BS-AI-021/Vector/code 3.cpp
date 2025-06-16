#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() 
{
    vector<int> numbers = {5, 2, 9, 1, 5, 6};
    sort(numbers.begin(), numbers.end());

    cout << "Sorted vector: ";
    for (int num : numbers) 
	{
        cout << num << " ";
    }
    
    cout << endl;
    return 0;
}