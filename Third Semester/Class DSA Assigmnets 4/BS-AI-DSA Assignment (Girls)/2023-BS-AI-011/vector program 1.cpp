//Write a program to add elements to a vector and display its size and capacity after each insertion.
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> myVector;

  // Add elements and display size and capacity
  for (int i = 0; i < 5; i++) {
    myVector.push_back(i + 1);
    cout << "Element " << i + 1 << " added." << endl;
    cout << "Size: " << myVector.size() << endl;
    cout << "Capacity: " << myVector.capacity() << endl;
  }

  return 0;
}