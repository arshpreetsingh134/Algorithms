// Implementing Breadth-First Search (BFS) of a graph using Queue (without using STL)
// Adjacency List Implementation for a Directed Acyclic Graph (DAG) without using an STL Library (besides... a vector)

// (For Undirected, uncomment lines 84 & 85)

#include <iostream>
#include <vector>
using namespace std;

/***** QUEUE IMPLEMENTATION *****/

// Adds an element at the end
void Enqueue(vector<int> &queue, int item)
{
    queue.push_back(item);
}

// Removes the first element
int Dequeue(vector<int> &queue)
{
    int first = queue[0];
    queue.erase(queue.begin());
    return first;
}

/***** QUEUE END *****/

/***** Adjacency List IMPLEMENTATION *****/

// DS to store info about a Node (or Vertex)
struct Node
{
    int val;
    Node *next;

    /** For constructing a Node **/
    Node(int val = 0, Node *next = nullptr)
    {
        this->val = val;
        this->next = next;
    }
};

// DS to store Graph Edges
struct Edge
{
    int src;
    int dest;
};

class Graph
{
    // No. of nodes in the graph
    int N;

public:
    // An array of pointers to Node to represent
    // adjacency list
    Node **head;

    // Constructor for constructing an undirected graph
    Graph(Edge edges[], int e, int N)
    {
        this->N = N;

        head = new Node *[N]();

        // initialize head pointer for all vertices
        // for (int i = 0; i < N; i++)
        //     head[i] = nullptr;

        // Add edges to the adjacency list
        for (int i = 0; i < e; i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;

            // Link the src Node to the dest
            Node *new_node = new Node(dest, head[src]);
            head[src] = new_node;

            // Similarly, link the dest Node to the src
            // (for undirected graph, uncomment the following 2 lines)
            // new_node = new Node(src, head[dest]);
            // head[dest] = new_node;
        }
    }

    vector<int> BFS(int s)
    {
        // Mark all the vertices as non-visited
        vector<bool> visited(N, false);

        // Create a Queue for BFS
        vector<int> queue;
        vector<int> visited_nodes;

        Enqueue(queue, s);
        visited[s] = true;

        int i = 0;

        while (!queue.empty())
        {
            // Dequeue a vertex from queue & store it in visited_nodes
            int curr_val = Dequeue(queue);
            visited_nodes.push_back(curr_val);

            Node *temp = head[curr_val];

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            while (temp != NULL)
            {
                if (!visited[temp->val])
                {
                    visited[temp->val] = true;
                    Enqueue(queue, temp->val);
                }
                temp = temp->next;
            }
        }
        return visited_nodes;
    }

    // Destructor
    ~Graph()
    {
        for (int i = 0; i < N; i++)
            delete[] head[i];

        delete[] head;
    }
};

// print all neighboring vertices of given vertex
void printList(Node *ptr)
{
    while (ptr != nullptr)
    {
        cout << " -> " << ptr->val << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

/***** Adjacency List END *****/

int main()
{
    Edge edges[] = {{0, 2},
                    {2, 0},
                    {0, 1},
                    {1, 2},
                    {2, 3},
                    {3, 3}};
    int N = 4;
    int e = sizeof(edges) / sizeof(edges[0]);

    Graph graph(edges, e, N);

    vector<int> visited_nodes = graph.BFS(2);

    // print adjacency list representation of graph
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        cout << i << " --";

        // print all its neighboring vertices
        printList(graph.head[i]);
    }

    cout << "\n\nGraph Traversal in BFS is: ";

    for (auto i : visited_nodes)
        cout << i << " ";
}