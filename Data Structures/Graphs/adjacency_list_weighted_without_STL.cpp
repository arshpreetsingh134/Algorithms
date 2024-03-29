// Implementation of both Directed and Undirected UNWEIGHTED Graph using Adjacency List
// without using the STL library

#include <iostream>
using namespace std;

// DS to store info about a Node (or Vertex)
struct Node
{
    int val;
    int weight;
    Node *next;

    /** For constructing a Node **/
    Node(int val = 0, int weight = -1, Node *next = nullptr)
    {
        this->val = val;
        this->weight = weight;
        this->next = next;
    }
};

// DS to store Graph Edges
struct Edge
{
    int src;
    int dest;
    int weight;
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
            int weight = edges[i].weight;

            // Link the src Node to the dest
            Node *new_node = new Node(dest, weight, head[src]);
            head[src] = new_node;

            // Similarly, link the dest Node to the src
            // (for directed graph, comment the following 2 lines)
            new_node = new Node(src, weight, head[dest]);
            head[dest] = new_node;
        }
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
        cout << " -> " << ptr->val << "("<<ptr->weight<<") ";
        ptr = ptr->next;
    }
    cout << endl;
}

int main()
{
    int N = 7;
    Edge edges[] = {{1, 6, 5}, {6, 3, 8}, {1, 3, 2}, {1, 2, 2}, {3, 4, 4}, {2, 4, 1}, {2, 5, 9}, {5, 4, 6}};

    int e = sizeof(edges) / sizeof(edges[0]);

    Graph graph(edges, e, N);

    // print adjacency list representation of graph
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        cout << i << " --";

        // print all its neighboring vertices
        printList(graph.head[i]);
    }
}