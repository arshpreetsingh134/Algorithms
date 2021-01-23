// Travelling Salesman Problem (to find the minimum Hamiltonian Path) using Naive Approach
// (n-1)! permutations

#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
#define n 4
using namespace std;

int minPath(vector<vector<int>> &costs, int S)
{
    vector<int> V;
    for(int i=0; i<n ; i++)
    {
        if(i!=S)
            V.push_back(i);
    }

    int min_cost = INT_MAX;

    do
    {
        int current_cost = 0;
        int k=S;
        for(int i=0; i<V.size(); i++)
        {
            current_cost+=costs[k][V[i]];
            k=V[i];
        }
        current_cost+=costs[k][S];
        
        min_cost = min(current_cost,min_cost);
        
    }while(next_permutation(V.begin(), V.end()));

    return min_cost;
}


int main()
{
    vector<vector<int>> costs{{1,2,3,3},
                              {5,12,9,10},
                              {4,2,5,8},
                              {4,4,9,0}};

    // S --> Vertex from which you have to start travelling
    cout<<"Minimum cost is: "<<minPath(costs, 0);

}