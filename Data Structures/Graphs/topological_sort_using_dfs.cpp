// Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that 
// for every directed edge u v, vertex u comes before v in the ordering. Topological Sorting 
// for a graph is not possible if the graph is not a DAG. O(V+E).

#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Graph
{
    int V; // No. of vertices

    list<int> *adj; // Array pointer containing adjacency lists

    // To keep track of visited nodes
    bool *visited;
    int *tops;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
        visited = new bool[V];      // to keep track of the visited nodes
        tops = new int[V];          // to store the Topological Ordering of the elements in the graph
    }

    void addEdge(int v, int item)
    {
        // Add item to v's list
        adj[v].push_back(item);
    }

    // Here, we are using an implicit stack (i.e., a recursive stack frame) for DFS
    void DFS(int s, int &current_label)
    {
        visited[s] = true;

        // Traverse recursively through the adjacent edges of s
        for (auto i : adj[s])
        {
            if (!visited[i])
                DFS(i, current_label);
        }

        // Set the precedence of the current node, store it in the array
        // and decrement current_label for the lower recursive stack nodes
        tops[s] = current_label;
        current_label--;
    }

    // Loop over each vertex in the connected components of the graph
    int *TopoSort()
    {
        // Mark all the nodes as unexplored initially
        for (int i = 0; i < V; i++)
            visited[i] = false;

        // To keep track of the ordering from higher to lower precedence (the f-values)
        int current_label = V - 1;

        // For each node in the graph G, call DFS and visit the nodes
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                DFS(i, current_label);
        }

        // Return the topological sorting of the nodes
        return tops;
    }
};

int main()
{
    int V = 5;
    Graph graph(V);

    // Graph #1
    // graph.addEdge(5, 0);
    // graph.addEdge(5, 2);
    // graph.addEdge(2, 3);
    // graph.addEdge(3, 1);
    // graph.addEdge(4, 0);
    // graph.addEdge(4, 1);

    // Graph #2
    // graph.addEdge(0,1);
    // graph.addEdge(0,2);
    // graph.addEdge(1,3);
    // graph.addEdge(2,3);

    // Graph #3
    graph.addEdge(1,0);
    graph.addEdge(0,2);
    graph.addEdge(2,1);
    graph.addEdge(0,3);
    graph.addEdge(3,4);

    int *tops = graph.TopoSort();

    for (int i = 0; i < V; i++)
        cout << tops[i] << " ";
}
