#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> marks = {68, 98, 75, 53, 62};
	for (int i = 0; i < 4; i++)
	{
		cout << "Marks " << i + 1 << " : " << marks[i] << endl;
	}
}