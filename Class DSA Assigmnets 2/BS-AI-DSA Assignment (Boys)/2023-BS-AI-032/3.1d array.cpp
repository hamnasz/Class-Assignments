#include <iostream>
using namespace std;
int main()
{
	int n, m, sum = 0, product = 1;
	cout << "Enter rows: ";
	cin >> n;
	cout << "Enter coloumns: ";
	cin >> m;
	int arr[n][m];
	cout << "Enter elements: ";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}
	cout << "Matrix is: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			sum = sum + arr[i][j];
		}
	}
	cout << "Sum of matrix is: " << sum << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			product = product * arr[i][j];
		}
	}
	cout << "Product/Factorial of matrix is: " << product << endl;
}