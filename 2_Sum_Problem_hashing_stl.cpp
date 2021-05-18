// 2-Sum Problem using Hash Table Data Structure- O(n)- Due to Constant Time Searching

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int countPairs(vector<int> &A, int sum)
{
    unordered_set<int> ht;
    
    // Keep track of the no. of pairs having the given sum
    int count = 0;

    for (int i = 0; i < A.size(); i++)
    {
        // Check if (sum-A[i]) exists in the Hash Table
        // If the element exists, pair exists!
        if (ht.find(sum - A[i]) != ht.end())
        {
            cout << "(" << A[i] << "," << sum - A[i]
                 << ")" << endl;
            count++;
        }

        // Keep adding elements side-by-side
        ht.insert(A[i]);
    }
    return count;
}

// -29, -8, -4, 0, 1, 6, 10, 12, 16, 45
// Sum = 16
int main()
{
    vector<int> A = {0, 1, -4, 45, 8, 12, -29, 6, 10, -8, 16};
    int sum = 16;

    int count = countPairs(A, sum);

    cout << "No. of Pairs having the sum " << sum << ": " << count;

    if (count == 0)
        cout << "\nNo 2 elements in the array has the sum " << sum;
}