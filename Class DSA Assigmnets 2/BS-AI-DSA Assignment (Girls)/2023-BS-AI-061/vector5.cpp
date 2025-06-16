#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<int> mark = {1,2,3,4,5,};
  mark.push_back(6);
  for (int mark :mark) {
    cout << mark << "\n";
  }
  return 0;
}
