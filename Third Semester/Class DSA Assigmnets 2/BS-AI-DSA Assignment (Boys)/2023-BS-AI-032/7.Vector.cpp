#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<string> students = {"Faisal", "Hashir", "Haseeb", "Tayyab", "Hanzla"};
	for (int i = 0; i < 4; i++)
	{
		cout << "Student " << i + 1 << " : " << students[i] << endl;
	}
}