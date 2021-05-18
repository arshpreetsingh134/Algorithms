// Calculate the no. of inversions in the array, i.e., when i < j but A[i] > A[j].

// Inversion Count for an array indicates – how far (or close) the array is from being sorted.
// If the array is already sorted then the inversion count is 0. If the array is sorted in the
// reverse order that inversion count is the maximum. (nC2 = n(n-1)/2)

#include <iostream>
using namespace std;

// 1. Naive Implementation (O(n^2))
int Invert1(int A[], int N)
{
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (A[i] > A[j])
                count++;
        }
    }
    return count;
}

// 2. Piggybagging on Merge Sort (will return the no. of inversions for each merge) (O(nlogn))
int Merge(int A[], int first, int mid, int last)
{
    int counter = 0;

    int n1 = mid - first + 1;
    int n2 = last - mid;

    int L[n1];
    int R[n2];
    int N = last - first + 1;

    for (int i = 0; i < n1; i++)
        L[i] = A[first + i];

    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int left = first;
    int right = mid + 1;
    int i = 0, j = 0;

    for (int k = first; k <= last; k++)
    {
        while (i < n1 && j < n2)
        {
            if (L[i] > R[j])
            {
                counter = counter + (mid - first - i + 1);
                A[k] = R[j++];
            }
            else if (L[i] <= R[j])
            {
                A[k] = L[i++];
            }
            k++;
        }

        while (i < n1)
            A[k++] = L[i++];

        while (j < n2)
            A[k++] = R[j++];
    }
    return counter;
}

int MergeSort(int A[], int N, int first, int last)
{
    if (first >= last)
        return 0;

    int inv_count = 0;
    int mid = (first + last) / 2;
    inv_count += MergeSort(A, N, first, mid);
    inv_count += MergeSort(A, N, mid + 1, last);
    inv_count += Merge(A, first, mid, last);

    return inv_count;
}

int main()
{
    int A[] = {8, 4, 1, 2};

    int N = sizeof(A) / sizeof(A[0]);

    cout << "No. of inversions for the above array: " << Invert1(A, N) << endl;
    cout << "No. of inversions for the above array: " << MergeSort(A, N, 0, N - 1) << endl;
}