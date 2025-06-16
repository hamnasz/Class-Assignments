#include<iostream>
using namespace std;
int main() {
    int n,sum=0,average;

    cout << "Enter size: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
    cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
    sum +=arr[i];
    }
    average = sum/n;
    cout<<"Average of array is: "<<average;
}