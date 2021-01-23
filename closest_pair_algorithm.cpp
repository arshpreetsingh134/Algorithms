#include<iostream>
#include<vector>
#include<utility>
#include<math.h>
using namespace std;

void merge(vector<int> &A, int p, int q, int r){
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

    int i=0, j=0;

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

void mergesort(vector<int> &A, int p, int r){
    int q = floor((p+r)/2);
    mergesort(A, p, q);
    mergesort(A, q+1, r);
    merge(A, p, q, r);
}

int main()
{
    vector<int> Px;
    vector<int> Py;
    vector<vector<int>> points{{2,1},
                               {3,2},
                               {4,1},
                               {1,2},
                               {3,3}};
    
    for(auto i:points)
    {
        Px.push_back(i[0]);
        Py.push_back(i[1]);
    }

    mergesort(Px, 0, Px.size()-1);
    mergesort(Py, 0, Py.size()-1);

    for(auto i:Px)
    {
        cout<<i<<" ";
    }
}