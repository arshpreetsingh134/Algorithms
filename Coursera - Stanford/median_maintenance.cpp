#include <iostream>
#include <limits.h>
#include <fstream>

#define DEF_HEAP_SIZE (10000)

using namespace std;

// Signum function to check balancing of both heaps
// = 0  if a == b  - heaps are balanced
// = -1 if a < b   - left contains less elements than right
// = 1  if a > b   - left contains more elements than right
int checkBalancing(int a, int b)
{
    if (a == b)
        return 0;

    return a > b ? 1 : -1;
}

// For swapping 2 elements in an array
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Following 2 functions used as Comparators...(*comp)

bool Greater(int a, int b)
{
    return a > b;
}

bool Smaller(int a, int b)
{
    return a < b;
}

int Average(int a, int b)
{
    return (a + b) / 2;
}

// Heap Abstract Class to minimize code duplication
// as much as possible
class Heap
{
public:
    Heap(int *Arr, bool (*c)(int, int)) : A(Arr), comp(c)
    {
        heapSize = -1;
    }

    // Interfaces of Heap ADT (used in both MaxHeap & MinHeap classes)
    virtual void Insert(int e) = 0;
    virtual int GetTop() = 0;
    virtual int ExtractTop() = 0;
    virtual int GetCount() = 0;

protected:
    // Comparator Prototype
    bool (*comp)(int, int);

    // Array to store Heap
    int *A;

    // Variable to keep track of Heap Size
    int heapSize;

    // Left child of parent
    int left(int i)
    {
        return 2 * i + 1;
    }

    // Right child of parent
    int right(int i)
    {
        return 2 * i + 2;
    }

    // Parent of a given child
    int parent(int i)
    {
        if (i <= 0)
            return -1;
        return (i - 1) / 2;
    }

    // To return the topmost element of a Min/Max Heap
    int top()
    {
        if (heapSize >= 0)
            return A[0];

        return -1;
    }

    // To return the size of Heap
    int count()
    {
        return heapSize + 1;
    }

    // HEAPIFY method (towards ROOT) for both Min-Heap and Max-Heap
    // comp() differentiates between the 2 Heaps
    // "Greater() --> MaxHeap, Smaller() --> MinHeap"
    void HEAPIFY(int i)
    {
        int l = left(i);
        int r = right(i);
        int key_node;

        if (l <= heapSize && comp(A[l], A[i]))
            key_node = l;
        else
            key_node = i;

        if (r <= heapSize && comp(A[r], A[key_node]))
            key_node = r;

        if (key_node == i)
            return;

        // swap
        swap(A[key_node], A[i]);

        HEAPIFY(key_node);
    }

    int extractTop()
    {
        if (heapSize < 0)
            return INT_MAX;

        int key_val = A[0];
        swap(A[0], A[heapSize]);
        heapSize--;
        HEAPIFY(0);

        return key_val;
    }

    void UPDATE_KEY(int i, int key)
    {
        int p = parent(i);

        if (comp(A[i], key))
            return;

        A[i] = key;
        while (i > 0 && comp(key, A[p]))
        {
            swap(A[i], A[p]);
            i = p;
            p = parent(i);
        }
    }

    void INSERT_KEY(int val)
    {
        heapSize++;
        if (comp(-INT_MAX, INT_MAX))
            A[heapSize] = INT_MAX;
        else
            A[heapSize] = -INT_MAX;

        UPDATE_KEY(heapSize, val);
    }
};

// Specialization child class of Heap to define Max-Heap
class MaxHeap : public Heap
{
public:
    // member initialization list
    MaxHeap() : Heap(new int[DEF_HEAP_SIZE], &Greater) {}

    void Insert(int e)
    {
        INSERT_KEY(e);
    }

    int GetTop()
    {
        return top();
    }

    int ExtractTop()
    {
        return extractTop();
    }

    int GetCount()
    {
        return count();
    }
};

// Specialization child class of Heap to define Min-Heap
class MinHeap : public Heap
{
public:
    // member initialization list
    MinHeap() : Heap(new int[DEF_HEAP_SIZE], &Smaller) {}

    void Insert(int e)
    {
        INSERT_KEY(e);
    }

    int GetTop()
    {
        return top();
    }

    int ExtractTop()
    {
        return extractTop();
    }

    int GetCount()
    {
        return count();
    }
};

int getMedian(int elem, int &m, Heap &left, Heap &right)
{
    // Check if the heaps are balanced or not
    int bal = checkBalancing(left.GetCount(), right.GetCount());

    switch (bal)
    {
    // More elements in Right Heap
    case -1:
        if (elem > m)
        {
            left.Insert(right.ExtractTop());
            right.Insert(elem);
        }
        else
        {
            left.Insert(elem);
        }

        m = left.GetTop();
        
        break;

    // Both left and right heaps are equal in size
    case 0:
        if (elem > m)
        {
            right.Insert(elem);
            m = right.GetTop();
        }
        else
        {
            left.Insert(elem);
            m = left.GetTop();
        }

        break;

    // More elements in Left Heap
    case 1:
        if (elem > m)
        {
            right.Insert(elem);
        }
        else
        {
            right.Insert(left.ExtractTop());
            left.Insert(elem);
        }
        m = left.GetTop();
        
        break;
    }
    return m;
}

int returnMedian(int A[], int n)
{
    Heap *left = new MaxHeap();
    Heap *right = new MinHeap();

    int median = 0;
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += getMedian(A[i], median, *left, *right);
    }

    delete left;
    delete right;

    return sum;
}

int main()
{
    int *array = new int[DEF_HEAP_SIZE];

    ifstream file("Median.txt");

    int count = 0;
    int x;

    // check that array is not already full
    // and read integer from file,

    while (count < DEF_HEAP_SIZE && file >> x)
        array[count++] = x;

    cout << "\nMedian: " << returnMedian(array, count) % 10000;

    file.close();
}