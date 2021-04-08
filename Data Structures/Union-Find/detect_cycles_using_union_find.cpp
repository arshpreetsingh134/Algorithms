// Detecting Cycles Using Disjoint Set (Union-Find) Data Structure
// Naive Implementation of Union-Find

#include <iostream>
#include <cstring>
#include <list>
using namespace std;

class Graph
{
    int V;
    list<int> *Adj; // Array of Adjacency Lists
    int *parent;
    bool *visited; // Keeps track of the vertices that have already been traced

public:
    Graph(int V)
    {
        this->V = V;
        Adj = new list<int>[V];
    }

    void addEdge(int u, int v)
    {
        // For an Undirected Graph
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }

    void returnEdges(int u)
    {
        cout << "\nEdges of " << u << " are: ";
        for (auto i : Adj[u])
            cout << i << " ";

        cout << parent[1];
    }

    // Union-Find DS starts...

    int Find(int v)
    {
        if (parent[v] == -1)
            return v;

        return Find(parent[v]);
    }

    void Union(int u, int v)
    {
        parent[u] = v;
    }

    bool isCycle()
    {
        visited = new bool[V * sizeof(int)];
        memset(visited, false, sizeof(int) * V);

        // Allocate memory for creating V subsets
        parent = new int[V * sizeof(int)];

        // Initialize all subsets as single element sets and
        // fill them with default value -1
        // Default Value is-1, means each subset is the parent
        // of its own set
        memset(parent, -1, sizeof(int) * V);

        // Iterate through all edges of graph, find subset of
        // both vertices of every edge, if both subsets are
        // same, then there is cycle in graph.
        for (int i = 0; i < V; i++)
        {
            for (auto j : Adj[i])
            {
                if (!visited[j])
                {
                    int x = Find(i);
                    int y = Find(j);

                    if (x == y)
                        return true;

                    Union(x, y);
                }
            }
            visited[i] = true;
        }

        return false;
    }
};

int main()
{
    Graph G(5);

    // G.addEdge(0,1);
    // G.addEdge(1,2);
    // G.addEdge(0,2);

    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 4);
    //G.addEdge(2, 4);

    if (G.isCycle())
        cout << "Cycle exists.\n";
    else
        cout << "Cycle doesn't exist.\n";
}