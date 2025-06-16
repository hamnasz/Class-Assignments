#include <iostream> 
using namespace std; 
int main() 
{ 
int arr[5], smallest; 

cout << "Enter 5 numbers:" << endl; 

for (int i = 0; i < 5; i++) 
{ 
cin >> arr[i]; 
} 
smallest = arr[0]; 
// Assume first element is the smallest 

//Applying loop through each element in the array
for (int i = 1; i < 5; i++) 
{ 
    if (arr[i] < smallest) 
{ 
  smallest = arr[i]; 
  } 
} 
//Shows smallest number on the screen
cout << "The smallest number is: " << smallest << endl; 

// Return 0 indicates that the program ended successfully
return 0; 
}
