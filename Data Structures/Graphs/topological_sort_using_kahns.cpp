// Topological Sort using Kahn's Algorithm. O(V+E).
// It is based on the fact that "a DAG G has at least one vertex with in-degree 0
// and one vertex with out-degree 0."

#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Graph
{
    int V;          // No. of Vertices
    list<int> *Adj; // Array of Adjacency Lists

public:
    Graph(int V)
    {
        this->V = V;
        Adj = new list<int>[V]();
    }

    // Add v to u's adjacency list
    void addEdge(int u, int v)
    {
        Adj[u].push_back(v);
    }

    vector<int> TopoSort()
    {
        vector<int> visited;        // An array to keep track of visited-so-far nodes (topological order)
        vector<int> indegree(V, 0); // An array to keep track of in-degrees of all nodes
        queue<int> q;               // A queue to keep track of BFS Nodes

        // Calculate in-degrees for all nodes
        for (int i = 0; i < V; i++)
            for (auto j : Adj[i])
                indegree[j]++;

        for (int i = 0; i < V; i++)
            if (indegree[i] == 0)
                q.push(i);

        while (!q.empty())
        {
            // Extract front of queue (or perform dequeue)
            // and add it to topological order
            int front = q.front();
            q.pop();
            visited.push_back(front);

            // Iterate through all the neighbouring nodes
            // of dequeued node u and decrease their in-degree
            // by 1
            for (auto i : Adj[front])
            {
                indegree[i]--;

                if (indegree[i] == 0)
                    q.push(i);
            }

            
        }
        return visited;
    }
};

int main()
{
    int V = 6;
    Graph graph(V);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(4, 2);
    graph.addEdge(4, 5);
    graph.addEdge(2, 5);

    vector<int> tops = graph.TopoSort();

    if (tops.size() != V)
    {
        cout << "Topological Order not possible because graph is not a DAG.\n";
        return 0;
    }

    cout << "\nTopological Ordering (if valid): ";
    for (int i = 0; i < tops.size(); i++)
        cout << tops[i] << " ";
}