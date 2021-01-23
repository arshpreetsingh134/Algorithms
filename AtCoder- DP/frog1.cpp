#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;

void printSeq(vector<int> cache)
{
    int i = 0;
    cout<<"\nThe frog jumps in a sequence : ";
    while(i<=cache.size())
    {
        cout<<i+1<<" --> ";
        i=cache[i];

        if(i==0)
            break; 
    }
}

int minCost(vector<int> &stones, vector<int> &cost, vector<int> &cache, int i)
{
    int N = stones.size();

    if(i>=N-1)
        return 0;

    else if(i==N-2)
    {
        cache[i] = N-1;
        return abs(stones[i]-stones[i+1]);
    }

    if(cost[i]>0)
        return cost[i];

    int temp1 = abs(stones[i]-stones[i+1]) + minCost(stones, cost, cache, i+1);
    int temp2 = abs(stones[i]-stones[i+2]) + minCost(stones, cost, cache, i+2);

    cout<<"\nFor "<<i<<" "<<temp1<<" "<<temp2;

    if(temp1>=temp2)
    {
        cost[i] = temp2;
        cache[i] = i+2;
    }
        
    else
    {
        cost[i] = temp1;
        cache[i] = i+1;
    }

    if(i==0)
        printSeq(cache);

    return cost[i];
}

int main()
{
    vector<int> stones{30,10,60,10,60,50};
    int N = stones.size(); 
    int i = 0;
    vector<int> cache(N, 0);
    vector<int> cost(N,0);
    
    cout<<"\nMinimum cost for the frog to travel from stone A to stone B is: "<<minCost(stones, cost, cache, i);
}