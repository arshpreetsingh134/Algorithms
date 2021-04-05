// Prim's Algorithm for finding the Minimum Spanning Tree (MST) of a graph using Min Heap

#include <iostream>
#include <vector>
#include <algorithm> // For std::make_heap()
#include <climits>
#include <sstream>
#include <fstream>
using namespace std;

// DS to store info about a Node (or Vertex)
struct Node
{
    int val;
    int weight; // Weight of edge joining this vertex & the source
    Node *next;

    /** For constructing a Node **/
    Node(int val = 0, int weight = -1, Node *next = nullptr)
    {
        this->val = val;
        this->weight = weight;
        this->next = next;
    }
};

// DS to store info about Graph Edges
struct Edge
{
    int src;
    int dest;
    int weight;

    Edge(){}

    Edge(int src, int dest, int weight)
    {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
};

class Graph
{
public:
    int N; // No. of vertices in the Graph

    // An array of pointers to Node to represent
    // adjacency list
    Node **head;

    Graph(Edge edges[], int e, int N)
    {
        this->N = N;

        head = new Node *[N]();

        // Adding edges to the Adjacency List
        for (int i = 0; i < e; i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;

            // Link the src node to the dest
            Node *new_node = new Node(dest, weight, head[src]);
            head[src] = new_node;

            // Link the dest node to the src
            new_node = new Node(src, weight, head[dest]);
            head[dest] = new_node;
        }
    }

    // Destructor of memory
    ~Graph()
    {
        for (int i = 0; i < N; i++)
            delete[] head[i];

        delete[] head;
    }
};

// Structure to represent a MinHeap Node
struct MNode
{
    int val;  // Value of the Node (numbered 0 to V-1)
    int dist; // Single Shortest Path of this node from the src node
              // INF, if node isn't explored yet
};

// Class to represent a MinHeap
class MinHeap
{
    int size;     // Number of heap nodes present currently
    int capacity; // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()

    struct MNode **Nodes; // Array of Adj Lists containing nodes

public:
    // A utility function to create a
    // new Min Heap Node
    MNode *newHeapNode(int val, int dist)
    {
        MNode *new_node = new MNode();
        new_node->val = val;
        new_node->dist = dist;

        return new_node;
    }

    // Constructor for initializing the Heap with default values
    // of size, capacity, and position of nodes
    MinHeap(int capacity, vector<int> &dist)
    {
        this->size = capacity;
        this->capacity = capacity;
        this->Nodes = new MNode *[capacity]();
        this->pos = new int[capacity];

        for (int v = 0; v < capacity; v++)
        {
            Nodes[v] = newHeapNode(v, dist[v]);
            pos[v] = v;
        }
    }

    // Swap two nodes of min heap
    // Needed for minHeapify()
    void swapNodes(MNode **a, MNode **b)
    {
        MNode *t = *a;
        *a = *b;
        *b = t;
    }

    // A standard function to heapify at given index i
    // This function also updates position of nodes when they are swapped.
    // Position is needed for decreaseKey()
    void minHeapify(int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest;

        if (l < size && Nodes[l]->dist < Nodes[i]->dist)
            smallest = l;
        else
            smallest = i;

        if (r < size && Nodes[r]->dist < Nodes[smallest]->dist)
            smallest = r;

        if (smallest == i)
            return;

        // The Nodes to be swapped in MinHeap
        MNode *smallestNode = Nodes[smallest];
        MNode *indexNode = Nodes[i];

        // Swap Positions
        pos[smallestNode->val] = i;
        pos[indexNode->val] = smallest;

        swapNodes(&Nodes[smallest], &Nodes[i]);

        minHeapify(smallest);
    }

    // Check if the given minHeap is ampty or not
    int isEmpty()
    {
        return size == 0;
    }

    // Remove & return element with the smallest priority (O(lgn))
    MNode *extractMin()
    {
        if (isEmpty())
            return nullptr;

        // Store the root node & last node
        MNode *min = Nodes[0];
        MNode *last_node = Nodes[size - 1];

        // Swap root node with last node
        Nodes[0] = last_node;

        // Update position of last node
        pos[min->val] = size - 1;
        pos[last_node->val] = 0;

        // Reduce heap size & Min-Heapify
        size--;
        minHeapify(0);

        return min;
    }

    // To update the Priority of position i in the Queue (O(logn))
    void decreaseKey(int v, int dist)
    {
        // Get position of current Node
        int i = pos[v];

        //int parent = ceil(i / 2) - 1;
        int parent = (i - 1) / 2;

        if (dist > Nodes[i]->dist)
        {
            cout << "New key greater than the current key.";
            return;
        }

        // Update Node's distance
        Nodes[i]->dist = dist;

        // Swim till the root to maintain the Min-Heap property
        while (i > 0 && Nodes[parent]->dist > dist)
        {
            // Swap this node with its parent (and their positions)
            pos[Nodes[i]->val] = parent;
            pos[Nodes[parent]->val] = i;
            swapNodes(&Nodes[i], &Nodes[parent]);

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    // A utility function to check if a given vertex
    // 'v' is in min heap or not
    bool isInMinHeap(int v)
    {
        if (pos[v] < size)
            return true;
        return false;
    }
};

void Prim(Graph *graph, int src)
{
    int V = graph->N; // No. of vertices in the graph

    // For keeping track of key values for each node
    // Fill each node's key as INF initially
    vector<int> key(V, INT_MAX);
    vector<int> mst;
    vector<int> parent(V);

    MinHeap *minHeap = new MinHeap(V, key);

    // Consider the first vertex
    minHeap->decreaseKey(src, 0);

    while (!minHeap->isEmpty())
    {
        // Extract the node with minimum weight
        MNode *minHeapNode = minHeap->extractMin();

        int u = minHeapNode->val;
        key[u] = minHeapNode->dist;
        mst.push_back(u);

        // Traverse through all the adjacent vertices of the
        // extracted vertex 'u' and update their keys in the heap
        Node *temp_node = graph->head[u];
        while (temp_node != NULL)
        {
            int v = temp_node->val;

            // If key of 'v' is greater than the current
            // frontier distance between 'u' and 'v', then
            // update it
            if (find(mst.begin(), mst.end(), v) == mst.end() &&
                minHeap->isInMinHeap(v) &&
                (key[u] != INT_MAX) &&
                key[v] > temp_node->weight)
            {
                key[v] = temp_node->weight;
                minHeap->decreaseKey(v, key[v]);
                parent[v] = u;
            }
            temp_node = temp_node->next;
        }
    }

    int sum = 0;
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " -- " << i << " ; Weight: " << key[i] << endl;
        sum += key[i];
    }

    cout << "\nTotal cost of this MST is: " << sum;
    //printArr(mst, key);
}

int main()
{
    int V = 501;
    // Edge edges[] = {{0, 1, 1}, {1, 3, 2}, {2, 3, 5}, {0, 2, 4}, {0, 3, 3}};

    Edge edges[2184];

    // Reading text from file
    fstream file;
    file.open("edges.txt", ios::in);

    string ss;
    int count = 0;

    while (getline(file, ss))
    {
        string temp = "";

        int splitStr[3];

        int i = 0;

        stringstream s1(ss);

        while (getline(s1, temp, ' '))
        {
            int num;
            stringstream geek(temp);
            geek >> num;
            splitStr[i] = num;
            temp = "";
            i++;
        }

        edges[count] = Edge(splitStr[0], splitStr[1], splitStr[2]);

        count++;
    }


    int e = sizeof(edges) / sizeof(edges[0]);
    Graph graph(edges, e, V);

    Prim(&graph, 1);
}