#include<iostream>
#include<array>
using namespace std;

int *sort(int *A, int n){
    int temp, j, loc;

    for(int i=0; i<n-1; i++){
        int j=i+1;
        loc=i;
        while(j!=n){
            if(A[loc]>A[j])
                loc=j;
            j++;
        }
        temp = A[i];
        A[i]=A[loc];
        A[loc] = temp; 
    }
    return A;
}

int main(){
    int A[] = {22, 55, 11, 88, 77, 33, 99, 44};
    int n= sizeof(A) / sizeof(A[0]);
    int *sorted = sort(A,n);
    cout<<"Sorted array is: ";
    for(int i=0; i<n; i++){
        cout<<*(sorted+i)<<" ";
    }
}