// Rod-Cutting Problem using Recursive (Naive) Approach
// Given a rod of length n inches and a table of prices p(i) for i=1,2,3,....,n, determine
// the maximum revenue r(n) obtainable by cutting up the rod and selling the pieces.

#include <iostream>
#include <climits>
using namespace std;

// price[0..n]
int rodCut(int *p, int n)
{
    int max_price, temp;
    if (n == 0)
        return 0;

    max_price = INT_MIN;
    for (int i = 1; i <= n; i++)
    {

        temp = rodCut(p, n - i); //n-i from 3 to 1

        if ((p[i - 1] + temp) > max_price)
            max_price = p[i - 1] + temp;
    }
    return max_price;
}

int main()
{
    // Given an array of prices for the 10 different pieces of rods
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 10;
    cout << "The most optimized solution for " << n << " is: " << rodCut(p, n);
}