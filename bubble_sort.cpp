#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int bubble1(int* A, int size){
    int temp=0, min=A[0];
    for(int i = 0; i<size-1; i++){
        temp=i;
        for(int j = i+1; j<size; j++){
            if(A[temp] > A[j]){
                temp=j;
            }
        }
        min=A[temp];
        A[temp]=A[i];
        A[i]=min;
    }
}

int bubble2(int *A, int size){
    int j;
    for(int i=0; i<size-1; i++){
        j=0;
        while(j<size-i-1){
            if(A[j] > A[j+1])
                swap(A[j+1], A[j]);
            j++;
        }
    }
}

int main(){
    int A[] = {63, 64, 32, 54, 66, 88, 12, 45, 72, 28, 61};
    int size = sizeof(A)/sizeof(A[0]);
    bubble2(A, size);
    cout<<"Sorted array is: ";
    for(int i=0; i<size; i++){
        cout<<A[i]<<" ";
    }
}