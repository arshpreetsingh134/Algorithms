// Find the i-th smallest integer within an array in O(n) expected time
// Piggybacking on QuickSort

#include <iostream>
#include <vector>
#include <iterator> // For std::iter_swap()
#include <cstdlib>  // For std::rand() and std::srand()
#include <ctime>    // For std::time
#include <fstream>  // For file stream (std::ifstream)
using namespace std;

int CreatePivot(vector<int> A, int l, int r)
{
    srand(time(NULL));
    int random = l + rand() % (r - l);

    // srand((unsigned)time(0));
    // int random = (rand() % (r-l+1));
    return random;
}

int PARTITION(vector<int> &A, int l, int r)
{
    int random = CreatePivot(A, l, r);
    iter_swap(A.begin() + l, A.begin() + random);

    int pivot = A[l];

    int i = l + 1;
    for (int j = l + 1; j <= r; j++)
    {
        if (A[j] < pivot)
        {
            iter_swap(A.begin() + i, A.begin() + j);
            i++;
        }
    }

    iter_swap(A.begin() + i - 1, A.begin() + l);

    return i-1;
}

int RSelect(vector<int> &A, int l, int r, int i)
{
    if ((r - l) <= 0)
        return A[r];

    int random = PARTITION(A, l, r);

    if (random == i)
        return A[i];

    if (random > i)
        return RSelect(A, l, random - 1, i);
    else
        return RSelect(A, random + 1, r, i);
}

// 1 3 6 9 19 22 25 48 71 77 83
int main()
{
    int i = 4;
    vector<int> A{6, 9, 22, 25, 48, 71, 1, 3, 19, 77, 83};

    cout << i << "-th order statistic is: " << RSelect(A, 0, A.size() - 1, i);
}