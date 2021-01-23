// Kadane's Algorithm- Finding maximum contiguous subsequence
// local_aximum(i) = max(A[i] , A[i] + local_maximum(A[i-1]))
#include<iostream>
#include<vector>
using namespace std;

int max_subseq(vector<int> A)
{
    
}

int main()
{
    vector<int> A{-2, 1, -3, 4, -1, 2, 10, -5, 4};
    max_subseq(A);
}