// Implementation of Count Inversions using Fenwick Tree (also supports negative & duplicate values)
// In this implementation, the values of the given array are changed to the corresponding values in the
// range [0...N] in such a way that the relative order of the elements in the new array is maintained.
// We use std::lower_bound() for this. O(nlog(n)).

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// To find the Least Significant Bit of a number
int lsb(int num)
{
    return (num & -num);
}

// Converts an array to an array with values from 1 to N
// and relative order of smaller and greater elements remains
// same. For example, {7, -90, 100, 1} is converted to
// {3, 1, 4 ,2 } and {8, 4, 1, 2} is converted to {4, 3, 1, 2}
void convert_arr(vector<int> &A)
{
    vector<int> B;
    vector<int> temp(A);
    sort(temp.begin(), temp.end());

    for (int i = 0; i < A.size(); i++)
        A[i] = (lower_bound(temp.begin(), temp.end(), A[i]) - temp.begin()) + 1;
}

// Returns sum of arr[0..index]. This function assumes
// that the array is preprocessed and partial sums of
// array elements are stored in Fw[].
int prefixSum(int Fw[], int index)
{
    int sum = 0;
    while (index > 0)
    {
        sum += Fw[index];
        index = index - lsb(index);
    }

    return sum;
}

// Updates a node in BIT at given index in
// the tree. The value 1 is added to Fw[i]
// and all of its ancestors in the tree.
void setCount(int Fw[], int i, int N)
{
    while (i <= N)
    {
        Fw[i] += 1;
        i = i + lsb(i);
    }
}

// Returns the no. of Inversion Counts of an array
int count_inv(vector<int> A)
{
    int inv_count = 0;
    int N = A.size();

    convert_arr(A); // First, convert the array values into relative ranges

    // Create a BIT with size equal to maxElement+1 (Extra
    // one is used so that elements can be directly be
    // used as index)
    int Fw[N + 1] = {0};

    // Traverse all elements from right
    for (int i = N - 1; i >= 0; i--)
    {
        inv_count += prefixSum(Fw, A[i] - 1);
        setCount(Fw, A[i], N);
    }

    // for (int i = 1; i < N + 1; i++)
    //     cout << Fw[i] << " ";

    return inv_count;
}

int main()
{
    vector<int> A{8, 4, 1, 4, 2};
    cout << "\nNo. of inversions: " << count_inv(A) << endl;

    vector<int> B{-2, 4, -25, 6, 18};
    cout << "\nNo. of inversions: " << count_inv(B) << endl;
}