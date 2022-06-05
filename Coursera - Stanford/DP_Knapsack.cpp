// This is a bottom-up implementation of 0-1 Knapsack Problem (along wiith Reconstruction) - O(n.W)
#include <iostream>
#include <vector>
#define ll long long int
using namespace std;

// Fill the 2-D Table cells one by one for each i <- {1..n}
ll knapsack(vector<ll> values, vector<ll> weights, vector<vector<ll>> &A, ll n, ll W)
{
    for (ll i = 1; i <= n; i++)
    {
        for (ll x = 1; x <= W; x++)
        {
            // If the current item's weight is greater than the overall weight limit in
            // the knapsack, ignore the second case...
            if (x < weights[i - 1])
            {
                A[i][x] = A[i - 1][x];
                continue;
            }

            // Either i-th item is not included (in which case it checks for prev "i-1" items
            // w.r.t. total weight W), or it is (in which case it checks for prev "i-1" cases
            // w.r.t. residual weight W-weights[i])
            A[i][x] = max(A[i - 1][x], A[i - 1][x - weights[i - 1]] + values[i - 1]);
        }
    }
    return A[n][W];
}

// Reconstruction Algorithm: To find the actual optimal solution, i.e., items that are selected
void reconstruct(vector<ll> values, vector<ll> weights, vector<vector<ll>> A, ll n, ll W)
{
    ll res = A[n][W];
    int w = W;
    for (ll i = n; i > 0 && res > 0; i--)
    {
        // Either the result comes from the top (A[i-1][w]) or
        // from (values[i-1] + A[i-1][w-weights[i-1]]) as in Knapsack
        // Table. If it comes from the latter one, it means the
        // item is included...
        if (res == A[i - 1][w]) // Current item not included, continue
            continue;
        else
        {

            // This item is included.
            cout << i << " ";

            // Since this weight is included its
            // value is deducted
            res = res - values[i - 1];
            w = w - weights[i - 1];
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    // for getting input from input.txt

    freopen("txt/knapsack1.txt", "r", stdin);

    // for writing output to output.txt
    freopen("txt/output.txt", "w", stdout);
#endif

    ll W;
    ll n;

    cin >> W >> n;

    vector<ll> values(n);
    vector<ll> weights(n);

    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
        cin >> weights[i];
    }

    vector<vector<ll>> A(n + 1, vector<ll>(W + 1, 0));

    cout << "The most optimal value for the Knapsack is: " << knapsack(values, weights, A, n, W) << endl;
    cout << endl;

    cout << "\nItems included in the Knapsack are: ";
    reconstruct(values, weights, A, n, W);
    cout << endl;
}
