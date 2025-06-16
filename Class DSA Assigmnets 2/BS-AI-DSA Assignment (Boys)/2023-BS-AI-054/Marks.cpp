#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> Subject = {"Dsa=80", "Eng=90", "Calculus=98", "THQ=100", "Ai=50", "SE=85"};
    
    for (int i = 0; i < Subject.size(); i++) {
        cout << Subject[i] << endl;
    }
    
    return 0;
}
