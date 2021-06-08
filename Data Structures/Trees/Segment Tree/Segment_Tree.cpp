// Implementation of Segment Tree Data Structure of resolving minimum range queries
// in O(log(n)) time

#include <iostream>
#include <cmath>
#include <limits.h>
#include <exception>
using namespace std;

class MyException : public exception
{
public:
    const char *what() const throw()
    {
        return "\n(EXCEPTION: Range outside the intervals...)";
    }
};

// Call this function recursively on subsequent nodes of the Segment Tree
int findMinUtil(int segTree[], int low, int high, int a, int b, int pos)
{
    // Complete Overlap --> a & b completely encompass the range of node
    if (a <= low && b >= high)
    {
        return segTree[pos];
    }

    // No Overlap --> The range of node is completely outside a & b
    else if (a > high || b < low)
        return INT_MAX;

    int mid = (low + high) / 2;

    // Partial Overlap
    return min(findMinUtil(segTree, low, mid, a, b, 2 * pos + 1),
               findMinUtil(segTree, mid + 1, high, a, b, 2 * pos + 2));
}

// Update the value in segment tree
void updateValUtil(int segTree[], int low, int high, int val, int i, int pos)
{
    // Base Case #1: If the index i lies outside the given segment range, then
    // don't go down that road, simply return...
    if (i < low || i > high)
        return;

    // Base Case #2: If the control reaches the leaf of segment tree, update value
    if (low == high)
    {
        segTree[pos] = val;
        return;
    }

    // else recursively update the current position w.r.t. the given index i
    int mid = (low + high) / 2;
    updateValUtil(segTree, low, mid, val, i, 2 * pos + 1);
    updateValUtil(segTree, mid + 1, high, val, i, 2 * pos + 2);

    segTree[pos] = min(segTree[2 * pos + 1], segTree[2 * pos + 2]);
}

// Minimum Range Querying (Find min. element b/w a & b) (O(log(n))
int minRangeQuery(int segTree[], int a, int b, int N)
{
    try
    {
        if (a < 0 || b >= N)
        {
            MyException e;
            throw e;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return findMinUtil(segTree, 0, N - 1, a, b, 0);
}

// Update a value in input array and segment tree. (O(log(n)))
void updateValue(int A[], int segTree[], int N, int val, int index)
{
    try
    {
        if (index < 0 || index >= N)
        {
            MyException e;
            throw e;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    cout << "\nUpdating index " << index << " from " << A[index] << " to " << val << endl;
    A[index] = val;

    // Use updateValUtil() recursively to update the value in segment tree
    updateValUtil(segTree, 0, N - 1, val, index, 0);
}

// Constructing the Segment Tree recursively (O(n))
void constructTree(int input[], int segTree[], int low, int high, int pos)
{
    // Base Case
    if (low == high)
    {
        segTree[pos] = input[low];
        return;
    }

    int mid = (low + high) / 2;
    constructTree(input, segTree, low, mid, 2 * pos + 1);           // Left Child
    constructTree(input, segTree, mid + 1, high, 2 * pos + 2);      // Right Child
    segTree[pos] = min(segTree[2 * pos + 1], segTree[2 * pos + 2]); // Root
}

// Print the original array as well as the Segment Tree related to that array
void printData(int A[], int N, int segTree[], int len)
{
    cout << "\nArray is: ";
    for (int i = 0; i < N; i++)
        cout << A[i] << " ";
    cout << "\nSegment Tree is: ";
    for (int i = 0; i < len; i++)
        cout << segTree[i] << " ";
    cout << endl;
}

int main()
{
    int a, b;
    int A[] = {2, 4, -8, 5, 6, 10};
    int N = sizeof(A) / sizeof(A[0]);

    // Max. Length of Segment Tree Array
    int len = 2 * pow(2, ceil(log2(N))) - 1;

    // Array for representing the Segment Tree DS
    int *segTree = new int[len];

    // Populate the Segment Tree Array with default values (INT_MAX)
    for (int i = 0; i < len; i++)
        segTree[i] = INT_MAX;

    constructTree(A, segTree, 0, N - 1, 0);

    printData(A, N, segTree, len);

    cout << "\n\nEnter the intervals for query: ";
    cin >> a >> b;

    cout << "\nMinimum in the range [" << a << "," << b << "]: " << minRangeQuery(segTree, a, b, N) << endl;

    updateValue(A, segTree, N, -6, 2);

    printData(A, N, segTree, len);

    cout << "\nEnter the intervals for query: ";
    cin >> a >> b;

    cout << "\nMinimum in the range [" << a << "," << b << "]: " << minRangeQuery(segTree, a, b, N) << endl;

    cout << endl;
}