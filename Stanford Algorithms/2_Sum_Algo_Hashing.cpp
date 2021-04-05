// 2-Sum Problem using Hash Table Data Structure- O(n)- Due to Constant Time Searching
#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
using namespace std;

bool countPairs(vector<long long int> &A, int sum)
{
    unordered_set<long long int> ht;

    // Keep track of the no. of pairs having the given sum
    int count = 0;

    for (int i = 0; i < A.size(); i++)
    {
        // Check if (sum-A[i]) exists in the Hash Table
        // If the element exists, pair exists!
        if (ht.find(sum - A[i]) != ht.end())
            return true;

        // Keep adding elements side-by-side
        ht.insert(A[i]);
    }
    //cout << sum << " ";
    return false;
}

// -29, -8, -4, 0, 1, 6, 10, 12, 16, 45
// Sum = 16
int main()
{
    vector<long long int> Arr;
    int count = 0;

    ifstream is("Median.txt");
    long long int x;

    while (is >> x)
        Arr.push_back(x);

    for (int sum = -10000; sum <= 10000; sum++)
    {
        if (countPairs(Arr, sum))
            count++;
    }

    cout << endl
         << Arr.size()<<endl;

    cout << "No. of sums that exist in the array: " << count;

    is.close();
}