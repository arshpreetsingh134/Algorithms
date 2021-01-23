// Merge + Insertion Sort

#include<bits/stdc++.h>
using namespace std;

void insert_sort(int *A, int l, int r){
    int i, key, j;
    for(j=l+1; j<=r; j++){
        int i=j-1;
        int key = A[j];
        while(i>=l && A[i]>key){
            A[i+1]=A[i];
            i--;
        }
        A[i+1]=key;
    }
}

void merge(int *A, int p, int q, int r){
    int n1 = q-p +1;
    int n2 = r-q;
    int *L = new int[n1];
    int *R = new int[n2];

    for(int i=0; i<n1; i++){
        L[i] = A[p+i];
    }

    for(int j=0; j<n2; j++){
        R[j] = A[q+j+1];
    }

    int i=0, j=0; //k=p;

    for(int k = p; k<=r; k++){
        if( (i<n1) && (j>=n2 || L[i]<=R[j])){
            A[k]=L[i];
            i++;
        }

        else{
            A[k]=R[j];
            j++;
        }
    }
}

    // while(i<n1 && j<n2){
    //     if(L[i] >= R[j]){
    //         A[k] = R[j];
    //         j++;
    //     }
    //     else if(L[i] < R[j]){
    //         A[k] = L[i];
    //         i++;
    //     }
    //     k++;
    // }

    // while (i < n1) { 
    //     A[k] = L[i]; 
    //     i++; 
    //     k++; 
    // }

    // while (j < n2) { 
    //     A[k] = R[j]; 
    //     j++; 
    //     k++; 
    // } 


void mergesort(int* A, int p, int r, int threshold){
    if((r-p)<=threshold)
        insert_sort(A, p, r);
    else{
    // if(p>=r)
    //      return;
    int q = floor((p+r)/2);
    mergesort(A, p, q, threshold);
    mergesort(A, q+1, r, threshold);
    merge(A, p, q, r);
    }
}

void printArray(int *A, int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        cout<<*(A+i)<<" ";
} 

int main(){
    int A[] = {6, 9, 22, 25, 48, 71, 1, 3, 19, 77, 83};

    int size = sizeof(A)/sizeof(A[0]);
    
    mergesort(A, 0, size-1, 2);
    cout<<"Sorted Array is: ";
    printArray(A, size);

}