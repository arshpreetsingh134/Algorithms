// Fenwick Tree (or Binary Indexed Tree) is a Data Structure used to perform update, pointer queries 
// and getSum operations on the range of elements of an array in O(logn) time. Compared with Segment 
// Tree, Fenwick Tree requires less space and is easier to implement.

#include <iostream>
using namespace std;

class FenwickTree
{
    int *tree; // To store values of a Fenwick Tree
    int N;     // Size of Fenwick Tree

    // Returns the value of the least significant bit (LSB)
    // lsb(108) = lsb(0b1101100) =     0b100 = 4
    // lsb(104) = lsb(0b1101000) =    0b1000 = 8
    // lsb(96)  = lsb(0b1100000) =  0b100000 = 32
    // lsb(64)  = lsb(0b1000000) = 0b1000000 = 64
    int lsb(int i)
    {
        // Taking AND of a number and it's 2's complement
        // isolates the lowest one bit value
        return (i & -i);
    }

    // Computes the prefix sum from [1, i], O(log(n))
    int prefixSum(int i)
    {
        int sum = 0;

        while (i != 0)
        {
            sum += tree[i];
            i = i - lsb(i);
        }

        return sum;
    }

public:
    FenwickTree(int values[], int size)
    {

        this->N = size;
        cout << "size is: " << N << endl;

        // Create an empty FT of size (N+1), since FT is 1-based array
        tree = new int(N + 1);

        tree[0] = 0;

        // Make a clone of the "values" array since we manipulate
        // the array in place destroying all its original content.
        for (int i = 0; i < N; i++)
        {
            tree[i + 1] = values[i];
        }

        // Fenwick Tree Construction
        for (int i = 1; i <= N; i++)
        {
            int parent = (i) + lsb(i);

            if (parent <= N)
                tree[parent] += tree[i];
        }

        // Printing the Fenwick Tree Array
        for(int i=0; i<N; i++)
            cout<<tree[i]<<" ";
    }

    // Returns the sum of the range [left, right], O(logn)
    int sum(int left, int right)
    {
        // Since the OG array is 0-based, we'll add 1 to 'left' and 'right'
        return prefixSum(right + 1) - prefixSum(left - 1 + 1);
    }

    // UPDATE: Update the value of index 'i' by 'v' (and all the subsequent indices), O(logn)
    void add(int i, int v)
    {
        while (i < N)
        {
            tree[i] += v;
            i = i + lsb(i);
        }
    }

    // SET: Set index 'i' to be equal to 'v', O(logn)
    void set(int i, int v)
    {
        add(i, v - sum(i, i));
    }
};

int main()
{
    int A[] = {5, -3, 6, 1, 0, -4, 11, 6, 2, 7};
    int size = sizeof(A) / sizeof(A[0]);

    FenwickTree *ft = new FenwickTree(A, size);

    cout << "\nSum of Range [2, 8] is: " << ft->sum(2, 8) << endl;

    ft->set(6, 20);

    cout << "Sum of Range [2, 8] is: " << ft->sum(2, 8) << endl;
}