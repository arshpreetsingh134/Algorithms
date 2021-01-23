// C++ code to find the most optimized path
// in a 2-D Grid

//0 represents the path is open, 1 represents the path is closed
#include<bits/stdc++.h>
using namespace std;

int min_value(int a, int b)
{
    if(a==0)
        return b;
    if(b==0)
        return a;
    if(a>b)
        return b;
    else
        return a;
}

string uniquePathsWithObstacles(vector<vector<int>>& A, int maxTime) 
{
	
	int r = A.size(), c = A[0].size(); 
	
	// create a 2D-matrix and initializing
	// with value 0
	vector<vector<int>> paths(r, vector<int>(c, 0));
	
	// Initializing the left corner if
	// no obstacle there
	if (A[0][0] == 0)
		paths[0][0] = 1;
		
	// Initializing first column of
	// the 2D matrix
	for(int i = 1; i < r; i++)
	{
		// If not obstacle
		if (A[i][0] == 0)
			paths[i][0] = paths[i-1][0] + 1;
	} 
	
	// Initializing first row of the 2D matrix
	for(int j = 1; j < c; j++)
	{
		
		// If not obstacle
		if (A[0][j] == 0)
			paths[0][j] = paths[0][j - 1] + 1;
	} 
	
	for(int i = 1; i < r; i++)
	{
		for(int j = 1; j < c; j++)
		{
			
			// If current cell is not obstacle 
			if (A[i][j] == 0)
				paths[i][j] = min_value(paths[i - 1][j], paths[i][j - 1]) + 1; 
		} 
	}
	
    cout<<paths[r-1][c-1];

	// Returning the corner value 
	// of the matrix
	if(paths[r-1][c-1]-1==0)
        return "No";

    if(paths[r-1][c-1]-1<=maxTime)
        return "Yes";
    else
        return "No"; 
}


int main()
{
    vector<vector<int>> A = {{0, 0, 1},
                            {1, 0, 0}};
                                
    cout << endl<< uniquePathsWithObstacles(A, 0) << " \n";											 
}
