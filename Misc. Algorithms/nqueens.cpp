// N-Queens Problem using Backtracking

#include<iostream>
#include<vector>
using namespace std;

bool checkQueen(vector<vector<int>> &table, int rows, int cols)
{
    // 'cols' leftmost queens have already been placed in the table

    int i,j;
    // right to left in a row
    for(i = cols-1; i>=0; i--)
    {
        if(table[rows][i]==1)
            return false;
    }

    // topleft to right-bottom in a diagonal
    for(i=rows, j=cols; i>=0 && j>=0; i--, j--)
    {
        if(table[i][j]==1)
            return false;
    }

    //bottom-left to top-right in a diagonal
    for(i=rows, j=cols; i<table.size() && j>=0; i++, j--)
    {
        if(table[i][j]==1)
            return false;
    }

    return true;
}

int NQueens(vector<vector<int>> &table, int cols)
{

    if (cols >= table.size()) 
        return true;

    for(int i = 0; i<table.size(); i++)
    {
        if(checkQueen(table, i, cols))
        {
            table[i][cols]=1;
            if(NQueens(table, cols+1))
                return true;

            table[i][cols]=0;

        }
    }
    return false;
}

int main()
{
    int N=4;
    vector<vector<int>> table(N, vector<int>(N, 0));

    cout<<"Pattern is : \n";
    NQueens(table, 0);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }
}