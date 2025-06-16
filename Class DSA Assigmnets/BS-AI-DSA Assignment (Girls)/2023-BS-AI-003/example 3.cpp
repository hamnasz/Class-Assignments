#include <iostream>
using namespace std;
int main() {
    string planets[4] = {"Earth", "Mars", "Jupiter", "Saturn"};
    for (int i=0;i<4;i++)
    {
    	cout<<i<<"="<<planets[i]<<"\n";
	}
    return 0;
}