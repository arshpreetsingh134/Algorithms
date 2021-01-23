// Finding the contiguous subarray having maximum sum in an array

#include<iostream>
using namespace std;

int calmax(int *A, int n){
    int current_max=0;
    int max=0;

    for(int i=0; i<n; i++){
        current_max=current_max+A[i];
        if(current_max<0)
            current_max=0;

        else if(max<current_max)
            max=current_max;
    }
    return max;
}

int calmax2(int *A, int n){
    int current_max=A[0], max1=A[0];

    for(int i=0; i<n; i++){
        current_max=max(A[i], current_max+A[i]);
        max1=max(current_max, max1);
    }
    return max1;
}

int main(){
    int A[]= {-2, -3, -4, -1, -2, -1, -5, -3};
    int size = sizeof(A)/sizeof(A[0]);
    cout<<"Maximum sum of the subarray is: "<<calmax2(A, size);
}