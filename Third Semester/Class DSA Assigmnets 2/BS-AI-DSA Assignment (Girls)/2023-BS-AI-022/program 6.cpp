#include <iostream>
#include <vector>
using namespace std;
int main() {
	
  vector<string> cars = {"Volvo", "BMW", "Ford", "Mazda"};
  cars.push_back("Tesla");
  cars.push_back("VW");
  cars.push_back("Mitsubishi");
  cars.push_back("Mini");

  for (string car : cars) {
    cout << car << "\n";
  }
  return 0;
}