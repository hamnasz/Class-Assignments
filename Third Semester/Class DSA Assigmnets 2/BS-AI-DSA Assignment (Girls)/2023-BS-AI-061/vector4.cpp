#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<string> girl = {"ayesha", "laiba", "shiza", "haiqa"};
  girl.push_back("sara");
  for (string girl :girl) {
    cout << girl << "\n";
  }
  return 0;
}
