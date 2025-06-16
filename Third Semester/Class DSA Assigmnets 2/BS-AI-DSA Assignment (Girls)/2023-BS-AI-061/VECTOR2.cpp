#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<string> BRANDS = {"ETHNIC", "HNM", "KHAADI", "PRIMARK"};
  BRANDS.push_back("SAPPHRE");
  for (string BRANDS : BRANDS) {
    cout << BRANDS << "\n";
  }
  return 0;
}
