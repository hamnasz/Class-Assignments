#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> myVector;

    for (int num = 1; num <= 5; num++) 
	{
        myVector.push_back(num);
        cout << "Current Size: " << myVector.size() <<endl; 
        cout<<"Current Capacity:"<< myVector.capacity() << endl;
    
    return 0;
}
}