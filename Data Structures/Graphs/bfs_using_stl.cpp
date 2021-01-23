// Breadth-First Search in a Directed/Undirected Graph, O(V+E)

// (For Undirected, uncomment line 29)

#include <iostream>
#include <list>
#include <queue>
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

        // For Undirected Graph, uncomment the following line
        // adj[item].push_back(v);
    }

    void BFS(int s)
    {
        bool *visited = new bool[V];

        // Mark all the vertices as non-visited initially
        for (int i = 0; i < V; i++)
            visited[i] = false;

        // Queue for BFS
        queue<int> q;

        // Mark the current node as visited and enqueue it
        visited[s] = true;
        q.push(s);

        // Keep traversing until the queue is empty
        while (!q.empty())
        {
            // Dequeue a vertex from queue & print it
            s = q.front();
            cout << s << " ";
            q.pop();

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (auto i : adj[s])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};

int main()
{

    Graph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(2, 0);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 3);
    graph.BFS(2);
}