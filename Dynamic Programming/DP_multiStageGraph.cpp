// Dynamic Programming
// Tracing the most optimal path from start to end in a Multi-Stage Graph using DP
// Directed Weighted Graph

#include<iostream>
#include<utility>
#include<vector>
#include<limits.h>
using namespace std;

int V=12;

void addEdge(vector <pair<int, int>> Adj[], int a, int b, int weight){

    // Adj[fromNode] = pair1(toNode1, weight1), pair2(toNode2, weight2).....

    Adj[a].push_back(make_pair(b, weight));
}

int cost(vector <pair<int, int>> Adj[], vector <pair<int, int>> c[], int N){
    if(N==V){
        c[N][0].first=0;
        c[N][0].second=V;
        return 0;
    }

    if(c[N][0].first>=0)
        return c[N][0].first;

    int temp;
    int min = INT_MAX;
    int toNode;
    for(auto i = Adj[N].begin(); i!=Adj[N].end(); i++){
        temp = i->second + cost(Adj, c, i->first);
        if(min > temp){
            min = temp;
            toNode = i->first;
        }
    }

    c[N][0].first=min;
    c[N][0].second=toNode;
    return min;   
}

void printGraph(vector <pair<int,int>> Adj[]){
    for(int i=0; i<V; i++){
        cout<<"\n\nNode "<<i<<" makes an edge with: \n";
        for(auto j = Adj[i].begin(); j!=Adj[i].end(); j++){
            cout<<"\tNode "<< j->first <<" with weight "<< j->second;
        }
    }
}

void tracePath(vector <pair<int,int>> c[], int Node){
    if(Node==12)
        return;
    int temp = c[Node][0].second;
    cout<<" --> "<<temp;
    tracePath(c, temp);
}

int main(){
    vector<pair<int, int>> Adj[V];
    
    // addEdge(Adj, fromNode, toNode, weight)

    addEdge(Adj, 1,2,9);
    addEdge(Adj, 1,3,7);
    addEdge(Adj, 1,4,3);
    addEdge(Adj, 1,5,2);
    addEdge(Adj, 2,6,4);
    addEdge(Adj, 2,7,2);
    addEdge(Adj, 2,8,1);
    addEdge(Adj, 3,6,2);
    addEdge(Adj, 3,7,7);
    addEdge(Adj, 4,8,11);
    addEdge(Adj, 5,7,11);
    addEdge(Adj, 5,8,8);
    addEdge(Adj, 6,9,6);
    addEdge(Adj, 6,10,5);
    addEdge(Adj, 7,9,4);
    addEdge(Adj, 7,10,3);
    addEdge(Adj, 8,10,5);
    addEdge(Adj, 8,11,6);
    addEdge(Adj, 9,12,4);
    addEdge(Adj, 10,12,2);
    addEdge(Adj, 11,12,5);
    //printGraph(Adj, V);

    vector<pair<int,int>> c[V+1];

    for(int i=0; i<V+1; i++){
        c[i].push_back(make_pair(-1,-1));
        addEdge(c, i, -1, -1);
    }


    cout<<"The most optimal path from 1 to "<<V<<" is: "<<cost(Adj, c, 1);
    cout<<"\nSequence of path traced will be: 1";
    tracePath(c, 1);
}