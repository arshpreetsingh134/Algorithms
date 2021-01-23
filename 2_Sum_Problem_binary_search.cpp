// 2-Sum Problem using Sorting & Binary Search- O(nlogn)
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

//********** BINARY SEARCH **********//
int binary_search(vector<int> &A, int a, int key, int b)
{
    int mid = floor((a + b) / 2);
    if (mid < a)
        return -1;
    if (A[mid] == key)
        return mid;

    if (A[mid] > key)
        return binary_search(A, a, key, mid - 1);
    else
        return binary_search(A, mid + 1, key, b);
}

// Returns the no. of pairs having the given sum
int checkSum(vector<int> &A, int sum)
{
    // First of all, sort the array in ascending order
    sort(A.begin(), A.end());

    // For keeping track of the no. of pairs with the sum
    int count = 0;

    // Now using Binary Search, find the elements equal
    // to (sum-t) for each t in the array
    for (int i = 0; i < A.size(); i++)
    {
        int r = binary_search(A, 0, sum - A[i], A.size() - 1);

        if (r != -1 && r != i) // (r!=i) to prevent end up searching for the same i-th element
        {
            cout << A[i] << " " << sum - A[i] << endl;
            count++;
        }
    }
    return count / 2;
}

// -29, -8, -4, 0, 1, 6, 10, 12, 16, 45
// Sum = 16
int main()
{
    vector<int> A = {0, 1, -4, 45, 8, 12, -29, 6, 10, -8, 16};
    int sum = 16;

    int count = checkSum(A, sum);

    cout << "No. of Pairs having the sum " << sum << ": " << count;

    if (count == 0)
        cout << "\nNo 2 elements in the array has the sum " << sum;
}