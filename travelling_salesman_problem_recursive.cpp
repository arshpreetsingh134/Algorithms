// Travelling Salesman Problem using simple recursion
#include<iostream>
#include<limits.h>
#include<vector>
#include<algorithm>
#define N 4
using namespace std;

void deleteVertex(vector<int> &V, int vertex)
{
    for(auto i = V.begin(); i!=V.end(); i++)
    {
        if(*i==vertex)
        {
            V.erase(i);
            return;
        }
    }
}

int traverse(vector<int> V, vector<vector<int>> costs, int from)
{
    
    deleteVertex(V, from);

    if(V.empty())
        return costs[from][0];
   
    int min_cost = INT_MAX;
    //V = {1,2,3}
   
    int current_cost;

    for(int i=0; i<V.size(); i++)
    {
        current_cost = costs[from][V[i]] + traverse(V, costs, V[i]);
        if(min_cost>current_cost)
            min_cost=current_cost; 
    }
    
    return min_cost;
}


int main()
{
    vector<vector<int>> costs{{1,2,3,3},
                              {5,12,9,10},
                              {4,2,5,8},
                              {4,4,9,0}};

    vector<int> V{0,1,2,3};
    
    cout<<"Minimum cost is: "<<traverse(V, costs, 0);
}