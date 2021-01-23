// Depth-First Search Implementation for Directed/Undirected Acyclic Graph
// (For Undirected, uncomment line 35)

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph
{
    int V; // No. of vertices

    list<int> *adj; // Array pointer containing adjacency lists

    bool *visited;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
        visited = new bool[V];

        // Mark all the vertices as non-visited initially
        for (int i = 0; i < V; i++)
            visited[i] = false;
    }

    void addEdge(int v, int item)
    {
        // Add item to v's list
        adj[v].push_back(item);

        // Add v to item's list
        //adj[item].push_back(v);
    }

    // Here, we are using an implicit stack (i.e., a recursive stack frame) for DFS
    void DFS(int s)
    {
        visited[s] = true;
        cout << s << " ";

        // Traverse recursively through the adjacent edges of s
        for (auto i : adj[s])
        {
            if (!visited[i])
            {
                DFS(i);
            }
        }
        //cout << s << " ";
    }
};

int main()
{

    Graph graph(5);

    // Graph #1
    graph.addEdge(1, 0);
    graph.addEdge(0, 2);
    graph.addEdge(2, 1);
    graph.addEdge(0, 3);
    graph.addEdge(3, 4);

    // Graph #2
    // graph.addEdge(0, 1);
    // graph.addEdge(0, 2);
    // graph.addEdge(1, 2);
    // graph.addEdge(2, 3);
    // graph.addEdge(2, 0);
    // graph.addEdge(3, 3);

    // graph.addEdge(5,0);
    // graph.addEdge(5,2);
    // graph.addEdge(2,3);
    // graph.addEdge(3,1);
    // graph.addEdge(4,0);
    // graph.addEdge(4,1);

    graph.DFS(0);
}