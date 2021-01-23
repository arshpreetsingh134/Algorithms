// Give an O(nlgk) time algorithm to merge k sorted lists into one sorted list,
// where n is the total number of elements in all the input lists.(k - way merging.)
// This algorithm also works for variable-sized lists...
#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <algorithm>
using namespace std;

// User-defined data structure for maintaining the elements 
// and indices for each of the k sorted lists
struct MinHeapElement
{
    // value @ A[i][j]
    int value;

    // index of the array from which the element is taken
    int i;

    // index of the next element to be picked from the array
    int j;
};

// For maintaing the min-heap property at position i (O(lgn))
void MIN_HEAPIFY(vector<MinHeapElement> &A, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest;

    if (l < A.size() && A[l].value < A[i].value)
        smallest = l;
    else
        smallest = i;

    if (r < A.size() && A[r].value < A[smallest].value)
        smallest = r;

    if (smallest == i)
        return;
    iter_swap(A.begin() + smallest, A.begin() + i);

    MIN_HEAPIFY(A, smallest);
}

// For building min - heap given an array, using MIN_HEAPIFY
// for each internal node (O(n)- tight bound, O(n lg n)- loose bound)
void BUILD_MIN_HEAP(vector<MinHeapElement> &A)
{
    for (int i = floor(A.size() / 2) - 1; i >= 0; i--)
    {
        MIN_HEAPIFY(A, i);
    }
}

// To update the Priority of position i in the Queue (O(lgn))
void HEAP_DECREASE_KEY(vector<MinHeapElement> &A, int i, int key)
{
    int parent = ceil(i / 2) - 1;
    if (key > A[i].value)
        return;

    // ceil(1/2) comes out to be 0 instead of 1 for some stupid reason idk,
    // so we are handling that scenario here
    // On a side note, it took me 2 f*cking days and more than 100 couts
    // just to debug this error. I'm done with coding now smh!!!!
    if (parent < 0)
        parent = 0;

    A[i].value = key;

    // Swim till the root to maintain the Min-Heap property
    while (i > 0 && A[parent].value > key)
    {
        iter_swap(A.begin() + i, A.begin() + parent);
        i = parent;
        parent = ceil(i / 2) - 1;
    }
}

// To insert an element inside the Priority Queue (O(lgn))
void MIN_HEAP_INSERT(vector<MinHeapElement> &A, MinHeapElement new_value)
{
    MinHeapElement temp;
    temp.value = INT_MAX;
    temp.i = new_value.i;
    temp.j = new_value.j;

    A.push_back(temp);
    HEAP_DECREASE_KEY(A, A.size() - 1, new_value.value);
}

// Delete the smallest element from the Min-Heap and return it
MinHeapElement MIN_HEAP_DELETE(vector<MinHeapElement> &A)
{
    MinHeapElement removed_node = A[0];
    
    iter_swap(A.begin(), A.rbegin());
    A.pop_back();
    MIN_HEAPIFY(A, 0);
    return removed_node;
}

// Bringing it all together
vector<int> MERGE(vector<vector<int>> &A)
{
    vector<int> sorted;
    vector<MinHeapElement> k_heap(A.size()); // size of k
    
    // Storing the first element from each of the k arrays into our Min Heap
    for (int b=0; b<A.size(); b++)
    {
        k_heap[b].value = A[b][0];
        k_heap[b].i = b;
        k_heap[b].j = 0;
    }
    
    // First we build the heap using the first elements each from the k arrays
    BUILD_MIN_HEAP(k_heap);

    // Then we check whether the heap is empty
    // As long as there are elements present in each of the k arrays, we
    // keep deleting the minimum elements from the heap & storing them into 'sorted'
    // and adding the element next to the deleted element to the Min Heap...
    while(!k_heap.empty())
    {
        MinHeapElement temp = MIN_HEAP_DELETE(k_heap);

        sorted.push_back(temp.value);

        // Insert the (j+1)th element from the ith list, if present
        if (temp.j+1<A[temp.i].size())
        {
            MinHeapElement new_value;
            new_value.value = A[temp.i][temp.j+1];
            new_value.i = temp.i;
            new_value.j = temp.j+1;
            MIN_HEAP_INSERT(k_heap, new_value);
        }
    }
    return sorted;
}

int main()
{
    vector<vector<int>> A{{8, 10, 13, 23},
                         {11, 20, 77, 98},
                         {12, 31, 44, 63, 110},
                         {21, 54, 33, 69, 70, 84}};

    for(auto i : MERGE(A))
        cout<<i<<" ";
}