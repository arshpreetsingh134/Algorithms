// Randomized QuickSort (Expected Running Time = Θ(nlgn))
#include <iostream>
#include <vector>
#include <iterator> // For std::iter_swap()
#include <cstdlib>  // For std::rand() and std::srand()
#include <ctime>    // For std::time
#include <fstream>  // For file stream (std::ifstream)
using namespace std;

// Select any number between l and r at random
int CreatePivot(vector<int> A, int l, int r)
{
    // Generate a random number in between
    // low .. high
    srand(time(NULL));
    int random = l + rand() % (r - l);
    return random;
}

// Generates Random Pivot by calling CreatePivot(), swapping pivot with
// end element and partitioning the array by taking last element as
// pivot, placing the pivot element at its correct position in sorted
// array, and placing all smaller (smaller than pivot) to left of
// pivot and all greater elements to right of pivot.
// Lomuto's Partitioning...
int PARTITION(vector<int> &A, int l, int r)
{
    // Pick a random index from l to r and swap
    // element at that index witih the first index element
    int random = CreatePivot(A, l, r);
    iter_swap(A.begin() + l, A.begin() + random);

    // Now choose the first element (now randomized) as pivot
    int pivot = A[l];

    // i -> first element just greater than the pivot
    // j -> boundary between the partitioned and unpartitioned elements
    int i = l + 1;
    for (int j = l + 1; j <= r; j++)
    {
        if (A[j] < pivot)
        {
            iter_swap(A.begin() + i, A.begin() + j);
            i++;
        }
    }

    // Place the pivot to its correct position after partitioning
    iter_swap(A.begin() + i - 1, A.begin() + l);

    return i-1;
}

// Recursively sort elements before and after the partitioning index 'random'
// by fixing random to it's position each time this subroutine is called
void QUICKSORT(vector<int> &A, int l, int r)
{
    if ((r - l) <= 0)
        return;

    int random = PARTITION(A, l, r);
    QUICKSORT(A, l, random - 1);
    QUICKSORT(A, random + 1, r);
}

int main()
{
    // vector<int> A{8, 9, 1, 2, 4, 7, 6, 12, 10, 16, 3, 20, 88, 44};

    vector<int> A;
    ifstream is("QuickSort.txt");
    int x;

    while (is >> x)

        A.push_back(x);

    cout<<endl;

    QUICKSORT(A, 0, A.size() - 1);

    for (auto i : A)
        cout << i << " ";
}
