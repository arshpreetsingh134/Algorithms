// Detecting a cycle in a Directed Graph using BFS (Kahn's Algorithm for Topological Sort)

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

    // Returns true if cycle(s) exist, else false
    bool isACycle()
    {
        vector<int> visited;        // An array to keep track of visited-so-far nodes (topological order)
        vector<int> indegree(V, 0); // An array to keep track of in-degrees of all nodes
        queue<int> q;               // A queue to keep track of BFS Nodes

        // Calculate in-degrees for all nodes
        for (int i = 0; i < V; i++)
            for (auto j : Adj[i])
                indegree[j]++;

        // int cnt=0;

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
            // cnt++;
        }

        cout << "\nTopological Ordering (if valid): ";
        for (auto i : visited)
            cout << i << " --> ";
        cout << endl;

        if (visited.size() == V)
            return false;
        else
            return true;
    }
};

int main()
{
    Graph G(5);
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 4);
    // G.addEdge(4, 2);
    G.addEdge(2, 3);
    G.addEdge(1, 3);

    bool isCycle = false;

    if (G.isACycle())
        isCycle = true;

    cout << "\nIs there a cycle in the graph? " << isCycle << endl;
}