// Program to compute all the Strongly Connected Components (SCCs) of a graph
// Kosaraju Algorithm (using dual DFS)

#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph
{
    int V; // No. of vertices

    list<int> *adj; // Array pointer containing adjacency lists

    bool *visited; // To keep track of the visited nodes

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
    }

    // To get the reverse (or transpose) of Graph
    Graph getTranspose()
    {
        Graph g(V);

        // Recurse through all vertices one by one
        for (int i = 0; i < V; i++)
        {
            // For each vertex, traverse through each of its adjacent
            // vertices and map them back to the vertex
            for (auto j : adj[i])
            {
                g.addEdge(j, i);
            }
        }

        return g;
    }

    // First DFS (on a reverse graph)
    // Fills Stack with vertices (in increasing order of finishing
    // times); the top element of stack has the maximum finishing
    // time ---> "for keeping track of f-values"
    void fillOrder(stack<int> &Stack, int s)
    {
        // Mark the current node as visited and print it
        visited[s] = true;

        // Recur for all the vertices adjacent to this vertex
        for (auto i : adj[s])
        {
            if (!visited[i])
            {
                fillOrder(Stack, i);
            }
        }

        // All vertices reachable from v are processed by now; push s to stack
        Stack.push(s);
    }

    // Second DFS (Recursive)
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
    }

    // The main function that finds and prints all strongly connected
    // components
    void printSCCs()
    {
        Graph g_rev(V);   // Reverse Graph
        stack<int> Stack; // For keeping track of f-values

        g_rev = getTranspose(); // Create a Reverse Graph

        // Fill vertices in stack according to their finishing times
        for (int i = 0; i < V; i++)
        {
            if (!g_rev.visited[i])
                g_rev.fillOrder(Stack, i);
        }

        // Now process all vertices in order defined by Stack
        while (!Stack.empty())
        {
            // Pop a vertex from stack
            int v = Stack.top();
            Stack.pop();

            // Print Strongly connected component of the popped vertex
            // by calling DFS for the second time
            if (!visited[v])
            {
                DFS(v);
                cout << endl;
            }
        }
    }
};

int main()
{

    Graph graph(6);

    // Graph #1
    // graph.addEdge(1, 0);
    // graph.addEdge(0, 2);
    // graph.addEdge(2, 1);
    // graph.addEdge(0, 3);
    // graph.addEdge(3, 4);

    // Graph #2
    // graph.addEdge(0, 1);
    // graph.addEdge(1, 2);
    // graph.addEdge(2, 0);
    // graph.addEdge(1, 3);
    // graph.addEdge(3, 4);
    // graph.addEdge(5, 4);
    // graph.addEdge(3, 5);
    // graph.addEdge(4, 10);
    // graph.addEdge(5, 4);
    // graph.addEdge(10, 5);
    // graph.addEdge(2, 6);
    // graph.addEdge(2, 7);
    // graph.addEdge(7, 6);
    // graph.addEdge(6, 8);
    // graph.addEdge(8, 9);
    // graph.addEdge(9, 7);
    // graph.addEdge(6, 9);
    // graph.addEdge(8, 10);

    graph.addEdge(0, 1);
    graph.addEdge(1, 3);
    graph.addEdge(5, 3);
    graph.addEdge(5, 4);
    graph.addEdge(0, 2);
    graph.addEdge(2, 4);

    graph.printSCCs();
}
