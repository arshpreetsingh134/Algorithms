// Dynamic Programming- Coin Change 2
// Coin change problem- Return the no. of possible combinations using the given coin values to make a change of 'amount'

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int change(int m, int n, vector<vector<int>> &A, vector<int> coins)
{
    if (n < 1)
    {
        A[m][n] = 1;
        return 1;
    }

    if (n > 0 && m < 1)
    {
        A[m][n] = 0;
        return 0;
    }

    if (A[m][n] > 0)
        return A[m][n];

    if (n - coins[m - 1] < 0)
        A[m][n] = change(m - 1, n, A, coins);
    else
        A[m][n] = change(m, n - coins[m - 1], A, coins) + change(m - 1, n, A, coins);

    return A[m][n];
}

int change2(int num_coins, int amount, vector<vector<int>> &A, vector<int> coins)
{
    // num_coins=3, amount=5
    for (int i = 0; i <= num_coins; i++)
    {
        for (int j = 0; j <= amount; j++)
        {

            if (j < 1)
            {
                A[i][j] = 1;
                continue;
            }

            if (i < 1 && j > 0)
            {
                A[i][j] = 0;
                continue;
            }

            if ((coins[i - 1] - j) > 0)
                A[i][j] = A[i - 1][j];
            else
                A[i][j] = A[i][j - coins[i - 1]] + A[i - 1][j];
        }
    }

    return A[num_coins][amount];
}

// Space-optimized Solution, O(n) complexity
int change3(int num_coins, int amount, vector<int> coins)
{
    vector<int> dp(amount + 1, 0);

    dp[0] = 1;

    for (int i = 0; i < num_coins; i++)
    {
        for (int j = coins[i]; j <= amount; j++)
        {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[amount];
}

int main()
{
    int amount = 10;
    vector<int> coins{2, 3, 5, 6};
    int num_coins = coins.size();
    vector<vector<int>> A(num_coins + 1, vector<int>(amount + 1, -1));

    //num_coins=3, amount=5

    cout << "No. of combinations to make a change of " << amount << " (Memoized): " << change(num_coins, amount, A, coins);
    cout << "\nNo. of combinations to make a change of " << amount << " (Bottom-Up): " << change2(num_coins, amount, A, coins);
    cout << "\nNo. of combinations to make a change of " << amount << " (Space-optimized): " << change3(num_coins, amount, coins);
}
