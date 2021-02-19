// Rotate a 2-D NxN matrix in 90° clockwise direction (O(n²) time, constant space)
#include <iostream>
#include <vector>
using namespace std;

void Rotate1(vector<vector<int>> &Mat)
{
    int temp;
    int N = Mat.size();

    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {
            temp = Mat[i][j];
            Mat[i][j] = Mat[N - j - 1][i];
            Mat[N - j - 1][i] = Mat[N - i - 1][N - j - 1];
            Mat[N - i - 1][N - j - 1] = Mat[j][N - i - 1];
            Mat[j][N - i - 1] = temp;
        }
    }
}

// Function for print matrix
void printMatrix(vector<vector<int>> &A)
{
    int N = A.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << " ";
        cout << '\n';
    }
}

int main()
{
    vector<vector<int>> A{{1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12},
                          {13, 14, 15, 16}};

    Rotate1(A);

    printMatrix(A);
}