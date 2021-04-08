// Implementation of finding MST using Kruskal Algorithm with the help of
// Disjoint Set / Union-Find Data Structure. O(MlogN)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Union_Find
{
    struct Edge
    {
    public:
        int u, v, weight;
        Edge(int u, int v, int weight)
        {
            this->u = u;
            this->v = v;
            this->weight = weight;
        }

        bool operator<(Edge const &other)
        {
            return weight < other.weight;
        }
    };

    void make_set(int i)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int V;
    int cost;
    
    vector<int> parent;
    vector<int> rank;
    vector<Edge> edges;
    vector<Edge> result;

    void swap(int &a, int &b)
    {
        int temp = b;
        b = a;
        a = temp;
    }

public:
    Union_Find(int V)
    {
        this->V = V;
        cost = 0;
        // edges.resize(V);
        parent.resize(V);
        rank.resize(V);

        for (int i = 0; i < V; i++)
            make_set(i);
    }

    void addEdge(int u, int v, int weight)
    {
        edges.push_back({u,v,weight});
    }

    int Find(int u)
    {
        if (parent[u] == u)
            return u;
        return parent[u] = Find(parent[u]);
    }

    void Union(int u, int v)
    {
        u = Find(u);
        v = Find(v);

        if (u != v)
        {
            if (rank[u] < rank[v])
                swap(u, v);

            parent[v] = u;
            if (rank[u] == rank[v])
                rank[u]++;
        }
    }

    void Kruskal()
    {
        sort(edges.begin(), edges.end());

        for(Edge e:edges)
        {
            if(Find(e.u)!=Find(e.v))
            {
                cost+=e.weight;
                result.push_back(e);
                Union(e.u, e.v);
            }
        }

        cout<<"Minimum Spanning Tree is: \n";
        for(auto e: result)
            cout<<e.u<<" "<<e.v<<" "<<e.weight<<endl;
    }

};

int main()
{
    Union_Find uf(5);

    uf.addEdge(0,1,1);
    uf.addEdge(1,2,4);
    uf.addEdge(2,3,2);
    uf.addEdge(3,4,6);
    uf.addEdge(1,4,5);
    uf.addEdge(0,4,7);
    uf.addEdge(1,3,3);

    uf.Kruskal();
}
