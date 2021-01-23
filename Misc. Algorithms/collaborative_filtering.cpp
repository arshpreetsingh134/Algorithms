// Given an array containing the first n numbers in some
// arbitrary order, output the number of inversions that
// can be performed for each pair (i,j) such that
// for all i<j, we have A[i] > A[j]
// Here, we'll be piggybacking on Merge Sort....

#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

int Count_Split_Inv(vector<int> &A, int p, int q, int r)
{
    int count_inv = 0;
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
            if(i<n1)
                count_inv+=n1-i;
            A[k]=R[j];
            j++;

        }

    }
    return count_inv;
}


int Inv_And_Count(vector<int> &A, int p, int r)
{
    if(p>=r)
        return 0;
    int mid = floor((p+r)/2);

    int x = Inv_And_Count(A, p, mid);
    int y = Inv_And_Count(A, mid+1, r);
    int z = Count_Split_Inv(A, p, mid, r);

    return (x+y+z);
}

int main()
{
    vector<int> A{2,1,3,4,5,6,9,8,14,7,10,11,12,13,15,18,16,17};

    // vector<int> A;

    // ifstream is("MyArray.txt");
    // int x;
    // while (is >> x)
    //     A.push_back(x);

    // is.close();
    
    int size = A.size();
    cout<<"\nSize is: "<<size;
    cout<<"\nTotal number of inversions: "<<Inv_And_Count(A, 0, size-1);

}