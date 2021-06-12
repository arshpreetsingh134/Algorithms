// This is a bottom-up implementation of 0-1 Knapsack Problem (along wiith Reconstruction) - O(n.W)
#include <iostream>
#include <vector>
using namespace std;

// Fill the 2-D Table cells one by one for each i <- {1..n}
int knapsack(vector<int> values, vector<int> weights, vector<vector<int>> &A, int n, int W)
{
    for (int i = 1; i <= n; i++)
    {
        for (int x = 1; x <= W; x++)  
        {
            // If the current item's weight is greater than the overall weight limit in
            // the knapsack, ignore the second case...
            if (x < weights[i-1])
            {
                A[i][x] = A[i - 1][x];
                continue;
            }

            // Either i-th item is not included (in which case it checks for prev "i-1" items
            // w.r.t. total weight W), or it is (in which case it checks for prev "i-1" cases
            // w.r.t. residual weight W-weights[i])
            A[i][x] = max(A[i - 1][x], A[i - 1][x - weights[i-1]] + values[i-1]);
        }
    }
    return A[n][W];
}

// Reconstruction Algorithm: To find the actual optimal solution, i.e., items that are selected
void reconstruct(vector<int> values, vector<int> weights, vector<vector<int>> A, int n, int W)
{
    int res = A[n][W];
    int w = W;
    for (int i = n; i > 0 && res > 0; i--)
    {
        // Either the result comes from the top (A[i-1][w]) or 
        // from (values[i-1] + A[i-1][w-weights[i-1]]) as in Knapsack 
        // Table. If it comes from the latter one, it means the
        // item is included...
        if (res == A[i - 1][w])         // Current item not included, continue
            continue;
        else
        {

            // This item is included.
            cout<<i<<" ";

            // Since this weight is included its
            // value is deducted
            res = res - values[i - 1];
            w = w - weights[i - 1];
        }
    }
}

int main()
{
    int n = 4;
    int W = 6;
    vector<int> values{3, 2, 4, 4};
    vector<int> weights{4, 3, 2, 3};
    vector<vector<int>> A(n + 1, vector<int>(W + 1, 0));

    cout << "The most optimal value for the Knapsack is: " << knapsack(values, weights, A, n, W) << endl;
    cout<<endl;

    cout<<"DP Table :-\n";
    for (auto i : A)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }

    cout<<"\nItems included in the Knapsack are: ";
    reconstruct(values, weights, A, n, W);
    cout<<endl;
}