#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    vec.clear();
    cout << "Vector size after clear: " << vec.size() <<endl;
    return 0;
}