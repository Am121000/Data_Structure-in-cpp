// Online C++ compiler to run C++ program online
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int arraysum(int n ,int *arr){
    if(n==0){
        return 0;
    }
    if(n==1){
        return arr[0];
    }
   int sum =arr[0]+arraysum(n-1,arr+1);
   return sum;

}
int main() {

    int n;
    cin>>n;
     int v1[n];
    for(int i=0;i<n;i++){
        cin>>v1[i];

    }
  int summ=arraysum(n,v1);
  cout<<summ<<endl;
    return 0;
}
