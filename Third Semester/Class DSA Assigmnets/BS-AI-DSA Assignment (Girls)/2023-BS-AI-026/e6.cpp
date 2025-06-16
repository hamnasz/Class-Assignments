#include <iostream>
using namespace std;
int main() {
    // Create a 2D array of 5 currencies and their corresponding country names
    string currencies[5][2];
    
    currencies[0][0] = "United States";   currencies[0][1] = "Dollar (USD)";
    currencies[1][0] = "United Kingdom";  currencies[1][1] = "Pound (GBP)";
    currencies[2][0] = "Japan";           currencies[2][1] = "Yen (JPY)";
    currencies[3][0] = "India";           currencies[3][1] = "Rupee (INR)";
    currencies[4][0] = "European Union";  currencies[4][1] = "Euro (EUR)";
    
    // Display the currencies and their countries
    cout << "Country and Currency List:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << currencies[i][0] << " - " << currencies[i][1] << endl;
    }

    return 0;
}
