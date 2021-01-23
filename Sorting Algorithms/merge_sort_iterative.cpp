// Non-recursive Merge Sort (also known as Two-Way Merge Sort)

#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

void merge(vector<int> &A, vector<int> &temp, int from, int to)
{
    // Here we'll be merging 2 already sorted subarrays A[from...mid] & A[mid+1...to]
    int mid = (from+to)/2;
    // int n1 = mid-from +1;
    // int n2 = to-mid;

    int i=from, j=mid+1;

    for(int k = from; k<=to; k++){
        if( (i<=mid) && (j>to || A[i]<=A[j]))
        {
            temp[k]=A[i];
            i++;
        }

        else{
            temp[k]=A[j];
            j++;
        }
    }

    for(int i=from; i<=to; i++)
    {
        A[i] = temp[i];
    }

}

void mergesort(vector<int> &A, vector <int> &temp, int low, int high)
{

    // low = 0, high = 7

    // divide the array into blocks of size m
    // m = [1, 2, 4, 6, 8,.....]
    for(int m=1; m<=high-low; m=m*2)
    {
        // for m=1 --> i = 0, 2, 4, 6, 8, ...
        // for m=2 --> i = 0, 4, 8, ...
        // for m=4 --> i = 0, 8, ...
        // and so on...

        for(int i=low; i<=high; i+=2*m)
        {
            int from = i;
            int to = min(i+2*m-1, high);
            merge(A, temp, from, to);
        }
    }
}


int main()
{
    vector<int> A{56,22,18,12,99,77,46,32};
    vector<int> temp(A.size());
    mergesort(A, temp, 0, A.size()-1);
    for(auto i:A)
        cout<<i<<" ";
}