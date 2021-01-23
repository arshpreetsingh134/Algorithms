// Computing the Shortest Path in a Weighted/Unweighted Graph using BFS, O(V+E)

// In this code for BFS, we keep track of dist(v), the fewest no. of edges on a path from s to v.

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <climits>

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

        // Add v to item's list
        adj[item].push_back(v);
    }

    int BFS(int s, int v)
    {
        // Vector to keep track of distances (s,v)
        vector<int> dist(V, INT_MAX);

        // Vector to store the predecessor of s (initialize every distance to -1)
        vector<int> pred(V, -1);

        // Distance from s to s is always 0 (base case)
        dist[s] = 0;

        // Predecessor of s is -1, since it's the starting node
        //pred[s] = -1;

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
            // cout << s << " ";
            q.pop();

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (auto i : adj[s])
            {
                if (!visited[i])
                {
                    dist[i] = dist[s] + 1;
                    pred[i] = s;
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << "Shortest Path is: ";

        int i = v;
        while (i != -1)
        {
            cout << i << "  ";
            i = pred[i];
        }

        return dist[v];
    }
};

int main()
{
    Graph graph(8);

    graph.addEdge(1, 2);
    graph.addEdge(1, 0);
    graph.addEdge(0, 3);
    graph.addEdge(3, 7);
    graph.addEdge(3, 4);
    graph.addEdge(7, 6);
    graph.addEdge(7, 4);
    graph.addEdge(4, 6);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);

    int s = 2;
    int dest = 6;

    cout << "\nShortest Path from " << s << " to " << dest << " is: " << graph.BFS(s, dest);
}