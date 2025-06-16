#include <iostream>
using namespace std;
int main()
{
	int n;
	cout<<"Enter the size of array: "<<endl;
	cin>>n;
	
	int arr[n];
	
	cout<<"Enter the elements of array: "<<endl;
	for(int i;i<n;i++){
		cin>>arr[i];
	}
	
	cout<<"\nThe prime numbers in array are: "<<endl;
	for(int i;i<n;i++){
		if(arr[i]>1){
			int j;
			for( j=2;j<arr[i];j++){
				if (arr[i]%j==0){
				
			cout<<"No prime number!"<<endl;
				break;
			}
	}
		if(j==arr[i]){
			cout<<arr[i]<<"\n";
		}

}
	}
	
cout<<endl;
return 0;
}