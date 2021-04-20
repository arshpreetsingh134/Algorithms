// Algorithm in which if an element in an MxN matrix is 0, its entire row and column are set to 0

#include <iostream>
#include <vector>
using namespace std;

void nullifyRow(vector<vector<int>> &A, int row)
{
    for (int i = 0; i < A[0].size(); i++)
        A[row][i] = 0;
}

void nullifyCol(vector<vector<int>> &A, int col)
{
    for (int i = 0; i < A.size(); i++)
        A[i][col] = 0;
}

// Approach 1: O(MN) time and O(M+N) space
void changeMatrix1(vector<vector<int>> &A)
{
    vector<bool> rows(A.size(), false);
    vector<bool> cols(A[0].size(), false);

    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[0].size(); j++)
        {
            if (A[i][j] == 0)
            {
                rows[i] = true;
                cols[j] = true;
            }
        }
    }

    // Nullify Rows
    for (int i = 0; i < A.size(); i++)
        if (rows[i])
            nullifyRow(A, i);

    // Nullify Columns
    for (int j = 0; j < A[0].size(); j++)
        if (cols[j])
            nullifyCol(A, j);
}

// Approach 2: O(MN) time and O(1) space
void changeMatrix2(vector<vector<int>> &A)
{
    bool rowHasZero = false;
    bool colHasZero = false;

    // Check if first row has a zero
    for (int i = 0; i < A[0].size(); i++)
    {
        if (A[0][i] == 0)
        {
            rowHasZero = true;
            break;
        }
    }

    // Check if first column has a zero
    for (int j = 0; j < A.size(); j++)
    {
        if (A[j][0] == 0)
        {
            colHasZero = true;
            break;
        }
    }

    // Check for zeros in the rest of the array
    for (int i = 1; i < A.size(); i++)
    {
        for (int j = 1; j < A[0].size(); j++)
        {
            if (A[i][j] == 0)
            {
                A[i][0] = 0;
                A[0][j] = 0;
            }
        }
    }

    // Nullify columns based on values in first row
    for (int i = 1; i < A[0].size(); i++)
        if (A[0][i] == 0)
            nullifyCol(A, i);

    // Nullify rows based on values in first column
    for (int j = 1; j < A.size(); j++)
        if (A[j][0] == 0)
            nullifyRow(A, j);

    // Nullify first row, if zero present
    if (rowHasZero)
        nullifyRow(A, 0);

    // Nullify first column, if zero present
    if (colHasZero)
        nullifyCol(A, 0);
}

// Function for printing matrix
void printMatrix(vector<vector<int>> &A)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[0].size(); j++)
            cout << A[i][j] << " ";
        cout << '\n';
    }
}

int main()
{
    vector<vector<int>> A{{0, 1, 6, 8},
                          {1, 2, 0, 7},
                          {7, 0, 2, 3},
                          {6, 10, 1, 12}};

    vector<vector<int>> B{{0, 1, 6, 8},
                          {1, 2, 0, 7},
                          {7, 0, 2, 3},
                          {6, 10, 1, 12}};

    changeMatrix1(A);
    printMatrix(A);

    cout << endl;

    changeMatrix2(B);
    printMatrix(B);
}