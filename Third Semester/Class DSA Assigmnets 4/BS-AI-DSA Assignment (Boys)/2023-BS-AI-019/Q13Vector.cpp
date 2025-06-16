// Add elements to a vector and display its size and capacity after each insertion

#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    vector<int> vec;

    cout << "Adding elements to the vector and displaying size and capacity:\n";
    
    // Loop to add elements from 0 to 9 to the vector
    for (int i = 0; i < 10; i++) 
    {
        vec.push_back(i);
        
        cout << "After inserting " << i << endl;
        cout << "Size: " << vec.size() << endl;     // Print the current size of the vector
        cout << "Capacity: " << vec.capacity() << endl; // Print the current capacity of the vector
    }

    return 0;
}

