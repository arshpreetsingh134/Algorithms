// Dynamic Programming Solution for calculating the Maximum-Weight Independent Set
// of a given path graph (No 2 Vertices in the IS should be adjacent)
// E.g.: 1 --> 4 --> 5 --> 4 (IS- {4,4} => Max. Weight = 8)
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long int
using namespace std;

// Bottom-up Approach...
// (Either select the optimal solution of the Graph G'' and the weight of i-th node,
//  or excude the i-th node and select the optimal solution of the Graph G')
vector<ll> calculateWeight(vector<ll> A)
{
    int i;
    int N = A.size();
    vector<ll> B(N + 1);
    B[0] = 0;
    B[1] = A[0];

    for (i = 2; i <= N; i++)
    {
        B[i] = max(B[i - 1], B[i - 2] + A[i - 1]);
    }

    return B;
}

void printSet(vector<ll> A, vector<ll> B, vector<int> C)
{
    int N = A.size();
    int i = N;
    vector<int> IS;

    while (i >= 2)
    {
        if (B[i] == B[i - 1])
            i--;
        else if (B[i] == B[i - 2] + A[i - 1])
        {
            IS.push_back(i);
            cout << i << " ";
            i -= 2;
        }
    }

    if (i == 1)
    {
        IS.push_back(i);
        cout << i << " ";
    }

    cout << "\n\nFor the given values: {1, 2, 3, 4, 17, 117, 517, 997}: (Present/Not Present?):\n";
    for (int i = 0; i < (int)C.size(); i++)
    {
        if (find(IS.begin(), IS.end(), C[i]) != IS.end())
            cout << 1;
        else
            cout << 0;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("txt/graph_weights.txt", "r", stdin);
    // for writing output to output.txt
    freopen("txt/output.txt", "w", stdout);
#endif

    int N;
    cin >> N;

    vector<ll> A(N);

    for (int i = 0; i < N; i++)
        cin >> A[i];

    vector<ll> B = calculateWeight(A);
    cout << "Max. Weight Independent Set has a total weight: " << B[N] << endl;


    cout << "\nIndependent Set for the given array is: ";

    vector<int> C{1, 2, 3, 4, 17, 117, 517, 997};
    printSet(A, B, C);

    return 0;
}
