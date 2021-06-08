// Dynamic Programming Solution for calculating the Maximum-Weight Independent Set
// of a given path graph (No 2 Vertices in the IS should be adjacent)
// E.g.: 1 --> 4 --> 5 --> 4 (IS- {4,4} => Max. Weight = 8)
#include <iostream>
using namespace std;

// Bottom-up Approach...
// (Either select the optimal solution of the Graph G'' and the weight of i-th node,
//  or excude the i-th node and select the optimal solution of the Graph G')
int *calculateWeight(int A[], int N)
{
    int i;
    int *B = new int[N + 1];
    B[0] = 0;
    B[1] = A[0];

    for (i = 2; i <= N; i++)
    {
        B[i] = max(B[i - 1], B[i - 2] + A[i - 1]);
    }

    return B;
}

// Print the Independent Set for the current array
void printSet(int A[], int B[], int N)
{
    int i = N-1;
    while (i >= 2)
    {
        if (B[i] == B[i - 1])
            i--;
        else if (B[i] == B[i - 2] + A[i - 1])
        {
            cout << A[i-1] << " ";
            i -= 2;
        }
    }

    if(i==1)
        cout<<A[i-1];
}

int main()
{
    int A[] = {1, 4, 5, 4};
    int N = sizeof(A) / sizeof(A[0]);

    int *B = calculateWeight(A, N);
    cout << "Max. Weight Independent Set has a total weight of: " << B[N] << endl;
    cout << "\nIndependent Set for the given array is: ";
    printSet(A, B, N + 1);
    cout<<endl;
}