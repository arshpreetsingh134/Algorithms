#include<bits/stdc++.h>
#include<cmath>

using namespace std;

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

void mergesort(int* A, int p, int r){
    if(p>=r)
         return;
    int q = floor((p+r)/2);
    mergesort(A, p, q);
    mergesort(A, q+1, r);
    merge(A, p, q, r);
}

int binary_search(int* A, int n, int key){
    int a = 0;
    int b = n-1;
    int mid = floor((a+b)/2);
    while(a<=b){
        int mid = floor((a+b)/2);
        if(A[mid]==key)
            return mid;
        else if(A[mid]>key)
        {
            b=mid-1;
        }
        else
        {
            a=mid+1;
        }
    }
    return -1;
}

bool pairExist1(int* A, int n, int x){

    int t;

    mergesort(A, 0, n-1);

    cout<<"Array after Merge Sort: ";
    for(int i=0; i<n; i++){
        cout<<A[i]<<" ";
    }

    for(int i=0; i<n; i++){
        t = binary_search(A, n, x-A[i]);  //31-ai

        if(t!=-1 && t!=i)
            return true;
    }
    return false;
}

bool pairExist2(int* A, int n, int x){
    int a = 0;
    int b = n-1;
    mergesort(A, a, b);

    while(a<=b){
        if(A[a] + A[b] == x)
            return true;
        else if (x < (A[a] + A[b]))
        {
            b--;
        }
        else
        {
            a++;
        }   
    }
    return false;
}

int main(){
    int A[] = {56, 10, 5, 42, 21, 33, 47};  // 5,10,21,33,42,47,56
    int n = sizeof(A)/sizeof(A[0]);
    int num = 16;
    bool check = pairExist2(A, n, num);
    cout<<"\nPair Exists for num "<<num<<"? "<<check;
}