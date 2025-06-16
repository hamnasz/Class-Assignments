#include <iostream>
using namespace std;
int main(){
	int  arr[5]= {1, 23, 45, 22, 19 };
	for (int i=0; i<=5;i++){
		cout<<arr[i]<<endl;
	}
		int smallest =arr[0];

	for (int i=0 ;i<=5;i++){

		if (arr[i]<smallest){
			smallest= arr[i];
			
}
		}
	cout<<"The Smallest no is        "<<smallest<<endl;			

}
