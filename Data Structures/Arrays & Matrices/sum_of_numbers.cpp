// Find the sum of 2 numbers represented as individual digits inside the 2 arrays.

#include <iostream>
#include <cmath>
using namespace std;

void addNumbers(int a[], int n, int b[], int m)
{
    int sum[n];
    int i = n - 1, j = m - 1, k = n - 1;
    int c = 0, s = 0;
    while (j >= 0)
    {
        s = a[i] + b[j] + c;
        sum[k] = (s % 10);
        c = s / 10;
        k--;
        i--;
        j--;
    }
    while (i >= 0)
    {
        s = a[i] + c;
        sum[k] = (s % 10);
        c = s / 10;
        i--;
        k--;
    }
    for (int i = 0; i <= n - 1; i++)
    {
        cout << sum[i];
    }
}

int main()
{
    int A[] = {2, 3, 4, 8};
    int B[] = {4, 8, 5};

    int alen = sizeof(A) / sizeof(A[0]);
    int blen = sizeof(B) / sizeof(B[0]);

    cout << "Sum of 2 numbers is: "; // 2348 + 485 = 2833

    addNumbers(A, alen, B, blen);
}