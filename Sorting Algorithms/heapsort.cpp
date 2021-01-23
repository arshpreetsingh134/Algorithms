// Implementation of Heapsort and Priority Queue procedures
// from CLRS

#include <iostream>
#include <vector>
#include <cmath>    // For std::floor and std::ceil
#include <limits.h> // For macro INT_MAX
#include <algorithm> // For std::iter_swap
using namespace std;

// For maintaing the max-heap property at position i (O(lgn))
void MAX_HEAPIFY(vector<int> &A, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest;

    if (l < A.size() && A[l] > A[i])
        largest = l;
    else
        largest = i;

    if (r < A.size() && A[r] > A[largest])
        largest = r;

    if (largest == i)
        return;

    iter_swap(A.begin() + largest, A.begin() + i);

    MAX_HEAPIFY(A, largest);
}

// For building max-heap given an array, using MAX_HEAPIFY
// for each internal node (O(n)- tight bound, O(n lg n)- loose bound)
void BUILD_MAX_HEAP(vector<int> &A)
{
    int n = A.size();
    for (int i = floor(n / 2) - 1; i >= 0; i--)
        MAX_HEAPIFY(A, i);
}

// O(nlgn) time
vector<int> HEAPSORT(vector<int> &A)
{
    BUILD_MAX_HEAP(A);
    vector<int> sorted;
    for (int i = A.size() - 1; i >= 1; i--)
    {
        iter_swap(A.begin(), A.begin() + i);
        A.pop_back();
        MAX_HEAPIFY(A, 0);
        sorted.insert(sorted.begin(), A[i]);
    }
    sorted.insert(sorted.begin(), A[0]);
    return sorted;
}

/* ************* PRIORITY QUEUE OPERATIONS ************ */
// Fetch the element with the maximum priority (O(1))
int HEAP_MAX(vector<int> A)
{
    return A[0];
}

// Remove & return element with the largest priority (O(lgn))
// Similar to poll()
int HEAP_EXTRACT_MAX(vector<int> &A)
{
    if (A.empty())
    {
        cout << "\nPriority Queue Underflow";
        return 0;
    }

    int max = A[0];
    iter_swap(A.begin(), A.rbegin());
    A.pop_back();
    MAX_HEAPIFY(A, 0);
    return max;
}

// To update the Priority of position i in the Queue (O(lgn))
void HEAP_INCREASE_KEY(vector<int> &A, int i, int key)
{
    int parent = ceil(i/2)-1;
    if (key < A[i])
    {
        cout << "New key smaller than the current key.";
        return;
    }
    A[i] = key;

    // Swim till the root to maintain the Max-Heap property
    while(i>0 && A[parent]<key)
    {
        iter_swap(A.begin()+i, A.begin()+parent);
        i = parent;
        parent = ceil(i / 2) - 1;
    }
}

// To insert an element inside the Priority Queue (O(lgn))
void MAX_HEAP_INSERT(vector<int> &A, int value)
{
    A.push_back(-INT_MAX);
    HEAP_INCREASE_KEY(A, A.size()-1, value);
}

int main()
{
    vector<int> A{16, 12, 15, 20, 31, 88, 4, 1, 10, 72, 93, 36};
    MAX_HEAPIFY(A, 0);

    for (auto i : A)
        cout << i << " ";

    BUILD_MAX_HEAP(A);

    cout << endl;

    for (auto i : A)
        cout << i << " ";

    // For sorting
    vector<int> sorted = HEAPSORT(A);

    cout << endl;

    for (auto i : sorted)
        cout << i << " ";

    cout << endl;

    // For Priority Queue
    vector<int> B{12, 13, 10, 8, 7, 2, 20, 19};
    BUILD_MAX_HEAP(B);

    for (auto i : B)
        cout << i << " ";

    cout << "\nHighest Priority: " << HEAP_EXTRACT_MAX(B);

    

    cout<<"\nUpdating 1st position's priority to 14... ";
    HEAP_INCREASE_KEY(B, 1, 14);

    cout << "\nAfter removal of root & increasing the priority, queue becomes: ";

    for (auto i : B)
        cout << i << " ";

    MAX_HEAP_INSERT(B, 23);

    cout<<"\nAfter insertion of key value 23, the priority queue becomes: ";

    for (auto i : B)
        cout << i << " ";
}