#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << "Element at index " << i << ": " << vec[i] <<endl;
    }
    return 0;
}