// 0-1 Knapsack Problem Using Dynamic Programming
// The 0-1 Knapsack Problem says that, given weights and values of n items,
// put these items in a knapsack of capacity W to get the maximum total value
// in the knapsack.

// Suppose that we are given two integer arrays val[0..n-1] and wt[0..n-1]
// which represent values and weights associated with n items respectively.
// Also given an integer W which represents knapsack capacity, we need to find
// out the maximum value subset of val[] such that the sum of the weights of this
// subset is smaller than or equal to W.

// Optimal Substructure: To consider all subsets of items, there can be two cases for every item.
// Case 1: The item is included in the optimal subset. (Value of nth item plus maximum value
//         obtained by n-1 items and W minus the weight of the nth item (including nth item).
// Case 2: The item is not included in the optimal set. (Maximum value obtained by n-1 items and
//         W weight (excluding nth item).

// Recurrence Relation: knapsack(val, W) = max(val[n] + knapsack(n -1, W-wt[n]), knapsack(n-1, W))

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(vector<int> &Weights, vector<int> &Prices, vector<vector<int>> &dp, int n, int W)
{
    if (n < 0)
        return 0;

    // if (W == 0)   // If the given weight constraint is equal to 0, then there are 0 ways in
    //     return 0; // which any of the n items get chosen. So the value returned will be 0.

    if (dp[n][W] != -1) // Check if the value of the subproblem is already present in the dp table
        return dp[n][W];

    if (Weights[n] > W)                             // If the weight of the i-th item is greater than the given weight constraint,
    {
        dp[n][W] = knapsack(Weights, Prices, dp, n - 1, W); // don't choose it.
        return dp[n][W];
    }
        
    dp[n][W] = max(Prices[n] + knapsack(Weights, Prices, dp, n - 1, W - Weights[n]), // Choose the n-th item
                   knapsack(Weights, Prices, dp, n - 1, W));                         // Or don't choose it

    cout << Prices[n] << " " << n << " --> " << dp[n][W] << endl;

    return dp[n][W];
}

int start_knapsack(vector<int> &Weights, vector<int> &Prices, int W)
{
    int items = Weights.size();
    vector<vector<int>> dp(items, vector<int>(W + 1, -1));
    return knapsack(Weights, Prices, dp, items - 1, W);
}

int main()
{
    vector<int> weights{5, 3, 4, 2};
    vector<int> prices{60, 50, 70, 30};
    int W = 5; // The given weight constraint

    int max_value = start_knapsack(weights, prices, W);

    cout << "\nThe Maximum Value for the given weight constraint " << W << " is: " << max_value;
}
