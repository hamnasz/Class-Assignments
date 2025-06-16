#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3}, 
                        {4, 5, 6}, 
                        {7, 8, 9}};
    int n = 3;
    int sumPrimary = 0, sumSecondary = 0;

    for (int i = 0; i < n; i++) {
        sumPrimary += matrix[i][i];                // Sum of primary diagonal
        sumSecondary += matrix[i][n - i - 1];      // Sum of secondary diagonal
    }

    cout << "Sum of primary diagonal: " << sumPrimary << endl;
    cout << "Sum of secondary diagonal: " << sumSecondary << endl;

    return 0;
}
