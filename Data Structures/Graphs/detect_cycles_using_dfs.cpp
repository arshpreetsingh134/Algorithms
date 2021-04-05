// Detecting cycles in a graph using DFS

// Approach: Depth First Traversal can be used to detect a cycle in a Graph. DFS for a connected graph produces a tree.
// There is a cycle in a graph only if there is a back edge present in the graph. To detect a back edge, keep track of 
// vertices currently in the recursion stack of function for DFS traversal. If a vertex is reached that is already in 
// the recursion stack, then there is a cycle in the tree. The edge that connects the current vertex to the vertex in 
// the recursion stack is a back edge. Use recStack[] array to keep track of vertices in the recursion stack.

#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph
{
    int V; // No. of vertices

    list<int> *adj; // Array pointer containing adjacency lists

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge(int v, int item)
    {
        // Add item to v's list
        adj[v].push_back(item);
    }

    // Here, we are using an implicit stack (i.e., a recursive stack frame) for DFS
    bool DFS(int v, bool visited[], bool recStack[])
    {
        if (!visited[v])
        {
            visited[v] = true;
            recStack[v] = true;

            // Traverse recursively through the adjacent edges of s
            for (auto i : adj[v])
            {
                if (!visited[i] && DFS(i, visited, recStack))
                    return true;
                else if (recStack[i])
                    return true;
            }
        }

        recStack[v] = false;
        return false;
    }

    bool isACycle()
    {
        bool *visited = new bool[V];  // To keep track of visited nodes
        bool *recStack = new bool[V]; // To keep track of the vertices present in the current recursive stack frame

        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }

        for (int i = 0; i < V; i++)
            if (DFS(i, visited, recStack))
                return true;

        return false;
    }
};

int main()
{
    int V = 6;
    Graph graph(V);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 3);

    bool isCycle = false;

    if (graph.isACycle())
        cout << "\nGraph contains cycle.";
    else
        cout << "\nGraph doesn't contain cycle.";

    cout << endl;
}