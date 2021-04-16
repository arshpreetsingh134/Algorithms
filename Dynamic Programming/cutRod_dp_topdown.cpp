// Dynamic Programming- Top-Down "Memoized" Approach for Optimized Rod Cutting Problem.

// Given a rod of length n inches and a table of prices p[i] for i = 1, 2, ...., n,
// determine the maximum revenue r[n] obtainable by cutting up the rod and selling the pieces.

#include <iostream>
using namespace std;

// Call this function recursively
int rodCutAux(int *p, int n, int *r)
{
    int max_price, temp;

    // If result already in DP Array, return it
    if (r[n] >= 0)
        return r[n];

    // Base Case
    if (n == 0)
        max_price = 0;

    else
    {
        max_price = -10000;
        for (int i = 1; i <= n; i++)
        {

            // Recurrence: r[n] = max(p[i] + r[n-i])   { for i = 0 to n-1 }

            temp = rodCutAux(p, n - i, r);
            if ((p[i - 1] + temp) > max_price)
                max_price = p[i - 1] + temp;
        }
    }

    // Memoizing- Storing the result of subproblems in the DP Array
    r[n] = max_price;
    return max_price;
}

int rodCut(int *p, int n)
{
    int *r = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
        r[i] = -10000;
    return rodCutAux(p, n, r);
}

int main()
{
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 4;
    cout << "The most optimized solution for " << n << " is: " << rodCut(p, n) << endl;
}