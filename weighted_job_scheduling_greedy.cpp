// Weighted Job Sceduling Problem- Given n jobs with {start time, finish time, profit}, find the max profit
// subset of jobs such that no 2 jobs overlap

#include <iostream>
#include <algorithm>
using namespace std;

struct Job
{
    int start, finish, profit;
};

// Comparator for sorting jobs in ascending order according to their
// finishing times
bool jobCompare(Job j1, Job j2)
{
    return j1.finish < j2.finish;
}

// Return the latest previous job that is not conflicting with the
// current job
int latestNonConflict(Job j[], int ind)
{
    for (int i = ind - 1; i >= 0; i--)
    {
        if (j[ind].start >= j[i].finish)
            return i;
    }
    return -1;
}

// Used by the third method (O(logn) for searching)
int binarySearch(Job j[], int ind)
{
    int low = 0;
    int high = ind-1;

    // Perform Binary Search
    while(low<=high)
    {
        int mid = (low+high)/2;

        if (j[mid].finish <= j[ind].start)
        {
            if(j[mid+1].finish <= j[ind].start)
                low = mid+1;
            else
                return mid;
        }
        else
            high = mid-1;
    }
    return -1;
}

// Method 1: A recursive function that returns the maximum
// possible profit from given array of jobs.  The array of 
// jobs must be sorted according to finish time. - O(n * 2^n)
int findMaxProfitRec(Job j[], int n)
{
    // Base Case
    if (n == 1)
        return j[n - 1].profit;

    // Including the current job
    int incl = j[n - 1].profit;

    int i = latestNonConflict(j, n-1);
    if (i != -1)
        incl += findMaxProfitRec(j, i + 1);

    // Excluding the current job
    int excl = findMaxProfitRec(j, n - 1);

    // Max of exclusive & inclusive
    return max(incl, excl);
}

int findMaxProfit1(Job j[], int n)
{    
    stable_sort(j, j + n, jobCompare);

    return findMaxProfitRec(j, n);
}

// Method 2: Using Dynamic Programming- O(n^2)
int findMaxProfit2(Job j[], int n)
{
    sort(j, j+n, jobCompare);

    // DP Table for storing the subproblems
    int* table = new int[n];
    table[0] = j[0].profit;
    int i;

    for(i=1; i<n; i++)
    {
        int incl = j[i].profit;
        int latest = latestNonConflict(j, i);

        // Evaluating profit including the current job
        if(latest!=-1)
            incl+= table[latest];

        // Evaluating profit excluding the current job
        int excl = table[i-1];

        table[i] = max(incl, excl);
    }

    return table[n-1];
}

// Method 3: Using DP and Binary Search - O(nlogn)
int findMaxProfit3(Job j[], int n)
{
    sort(j, j + n, jobCompare);

    // DP Table for storing the subproblems
    int *table = new int[n];
    table[0] = j[0].profit;
    int i;

    for (i = 1; i < n; i++)
    {
        int incl = j[i].profit;
        int latest = binarySearch(j, i);

        // Evaluating profit including the current job
        if (latest != -1)
            incl += table[latest];

        // Evaluating profit excluding the current job
        int excl = table[i - 1];

        table[i] = max(incl, excl);
    }

    return table[n - 1];
}

int main()
{
    Job arr[] = {{3, 5, 20}, {1, 2, 50}, {6, 19, 100}, {6, 100, 200}};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "The profit is (using Recursion): " << findMaxProfit1(arr, n);
    cout << "\nThe optimal profit is (using DP): " << findMaxProfit2(arr, n);
    cout << "\nThe more optimal profit is (using DP & Binary Search): " << findMaxProfit3(arr, n);
}

