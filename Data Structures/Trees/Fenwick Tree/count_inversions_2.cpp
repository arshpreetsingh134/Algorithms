// Implementation of Count Inversions using Fenwick Tree (O(nlog(maxElement)))
// (doesn't work on negative & duplicate values)
#include <iostream>
#include <climits>
using namespace std;

// Get the sum of range [0,i] in the Fenwick Tree
int getSum(int tree[], int i)
{
    int sum = 0;
    while (i > 0)
    {
        sum += tree[i];
        i -= (i & -i); // Cascade one LSB down
    }

    return sum;
}

void updatePointer(int tree[], int i, int N, int v)
{
    while (i <= N)
    {
        tree[i] += v;
        i += (i & -i);
    }
}

int countInv(int A[], int N)
{
    int max = INT_MIN;

    for (int i = 0; i < N; i++)
    {
        if (max < A[i])
            max = A[i];
    }

    int *tree = new int[max + 1];

    for (int i = 0; i <= max; i++)
        tree[i] = 0;

    int inv_count = 0;

    for (int i = N - 1; i >= 0; i--)
    {
        inv_count += getSum(tree, A[i]);
        updatePointer(tree, A[i], max + 1, 1);
    }
    return inv_count;
}

int main()
{
    int A[] = {8, 4, 1, 2};
    int N = sizeof(A) / sizeof(A[0]);
   
    cout << "\nNo. of Count Inversions: " << countInv(A, N) << endl;
}