#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec = {5, 10, 15, 20};
    cout << "Vector elements using iterators: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout <<endl;
    return 0;
}