#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int binary_search1(int *A, int a, int key, int b)
{

    while (a <= b)
    {
        int mid = floor((a + b) / 2);
        if (A[mid] == key)
            return mid;
        else if (A[mid] > key)
        {
            b = mid - 1;
        }
        else
        {
            a = mid + 1;
        }
    }
    return -1;
}

int binary_search2(int *A, int a, int key, int b)
{
    int mid = floor((a + b) / 2);
    if (mid < a)
        return -1;
    if (A[mid] == key)
        return mid;

    if (A[mid] > key)
        return binary_search2(A, a, key, mid - 1);
    else
        return binary_search2(A, mid + 1, key, b);
}

int main()
{
    int A[] = {56, 48, 78, 12, 58, 63, 22, 10};
    int size = sizeof(A) / sizeof(A[0]);
    sort(A, A + size);
    cout << "Array is: ";
    for (int i = 0; i < size; i++)
    {
        cout << A[i] << " ";
    }
    int key = 77;

    int ind = binary_search1(A, 0, key, size - 1);
    cout << "\nThe key " << key << " is found at: ";
    if(ind==-1)
        cout<<ind;
    else
        cout<<ind+1;
}
