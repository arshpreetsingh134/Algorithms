// Compute the Connected Components ("pieces") of an Undirected Graph G, O(V+E)
// Piggybacking on BFS

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

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
        visited = new bool[V];
    }

    void addEdge(int v, int item)
    {
        // Add item to v's list
        adj[v].push_back(item);

        adj[item].push_back(v);
    }

    void BFS(int s)
    {
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
        cout << " - ";
    }

    int connected_components()
    {
        int temp = 0;

        // Mark all the vertices as non-visited initially
        for (int i = 0; i < V; i++)
            visited[i] = false;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                temp++;
                BFS(i);
            }

        }
        return temp;
    }
};

int main()
{

    Graph graph(10);

    graph.addEdge(0, 2);
    graph.addEdge(0, 4);
    graph.addEdge(4, 2);
    graph.addEdge(4, 6);
    graph.addEdge(4, 8);

    graph.addEdge(1, 3);

    graph.addEdge(5, 7);
    graph.addEdge(7, 9);
    graph.addEdge(5, 9);

    cout<<"\nNo of connected components: "<<graph.connected_components();
}