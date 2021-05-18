// 2-Sum Problem using Sorting & Double Pointers (first & last)- O(nlogn)

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Returns the no. of pairs having the given sum
int checkSum(vector<int> &A, int sum)
{
    // First of all, sort the array in ascending order
    sort(A.begin(), A.end());

    // For keeping track of the no. of pairs with the sum
    int count = 0;

    int l = 0;            // First term pointer
    int r = A.size() - 1; // Last term pointer

    while (l < r)
    {
        if (A[l] + A[r] == sum)
        {
            count++; // If pair found, increase the count
            cout << A[l] << " " << A[r] << endl;
            l++;
            r--;
        }

        // If pair's sum less than the given sum,
        // increase the first pointer
        else if (A[l] + A[r] < sum)
            l++;

        // If pair's sum greater than the given sum,
        // decrease the last pointer
        else
            r--;
    }
    return count;
}

// -29, -8, -4, 0, 1, 6, 10, 12, 16, 45
// Sum = 16
int main()
{
    vector<int> A = {0, 1, -4, 45, 12, -29, 6, 10, -8, 16};
    int sum = 16;

    int count = checkSum(A, sum);

    cout << "No. of Pairs having the sum " << sum << ": " << count;

    if (count == 0)
        cout << "\nNo 2 elements in the array has the sum " << sum;
}