#include <iostream>
#include <string>
using namespace std;

int main()
{
  // Declare and initialize an array of strings named 'cars' with 5 elements
  string Phones[5]={"Samsung", "Oppo", "Tecno", "Realme", "Oneplus"};
  
  // Applying loop through each element in the array 
  for(int i = 0; i < 5; i++)
  {
  	// Output each element in the 'cars' array followed by a newline character
  	cout << Phones[i] << "\n"; 
  }
  
  // Return 0 indicates that the program ended successfully
  return 0;	
}

