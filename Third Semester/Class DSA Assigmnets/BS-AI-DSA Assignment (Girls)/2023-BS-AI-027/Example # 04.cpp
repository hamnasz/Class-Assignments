#include <iostream> 
using namespace std; 
int main()
 { 
// Initializing an array of size 5 
int numbers[5] = {10, 20, 30, 40, 50};  

// Loop through the array elements 
for (int i = 0; i < 5; i++) 
{ 
// Output the current element with its index 
cout << "Element at index " << i << " is: " << numbers[i] << endl; 
} 

// Return 0 indicates that the program ended successfully
return 0; 
}
