#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<string> cars = {"Volvo", "BMW", "Ford", "Mazda"};

  // Change the value of the first element
  cars.at(0) = "HAMZA";

  cout << cars.at(0);
  return 0;
}
