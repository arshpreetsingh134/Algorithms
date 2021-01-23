// Dijkstra's Algorithm using Min Heap (O(V + ElogV))

// Uncomment lines 72, 73 for Undirected Version

// In Dijkstra’s algorithm, two sets are maintained, one set contains list
// of vertices already included in SPT (Shortest Path Tree), other set contains
// vertices not yet included. Min Heap is used as a priority queue to get the
// minimum distance vertex from set of not yet included vertices. Time complexity
// of operations like extract-min and decrease-key value is O(LogV) for Min Heap.

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

#include <list>
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
public:
    // No. of nodes in the graph
    int N;

    // An array of pointers to Node to represent
    // adjacency list
    Node **head;

    // Constructor for constructing an undirected graph
    Graph(Edge edges[], int e, int N)
    {
        this->N = N;

        head = new Node *[N]();

        // Add edges to the adjacency list
        for (int i = 0; i < e; i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;

            // Link the src Node to the dest
            Node *new_node = new Node(dest, weight, head[src]);
            head[src] = new_node;

            // For an Undirected Graph, uncomment the following lines
            // new_node = new Node(src, weight, head[dest]);
            // head[dest] = new_node;
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

// Structure to represent a MinHeap Node
struct MNode
{
    int val;  // Value of the Node (numbered 0 to V-1)
    int dist; // Single Shortest Path of this node from the src node
              // INF, if node isn't explored yet
};

// Structure to represent a MinHeap
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

    // To update the Priority of position i in the Queue (O(lgn))
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

// A utility function used to print the solution
void printArr(vector<int> &dist, int n)
{
    cout << "Vertex   Distance from Source\n";
    for (int i = 0; i < n; ++i)
        cout << i << " \t\t " << dist[i] << endl;
}

// Main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void Dijkstra(Graph *graph, int src)
{
    // Get the no. of vertices in the graph
    int V = graph->N;

    // For keeping track of dist values for each node
    // Fill each node's dist as INF initially
    vector<int> dist(V, INT_MAX);

    // Initialize MinHeap
    MinHeap *minHeap = new MinHeap(V, dist);

    // Make dist vertex of src vertex 0 so that it is extracted first
    minHeap->decreaseKey(src, 0);

    // In the following loop, minHeap contains
    // all the nodes whose shortest distance is
    // not yet evaluated (unexplored)
    while (!minHeap->isEmpty())
    {
        // Extract the node with Min Distance Value
        MNode *minHeapNode = minHeap->extractMin();

        // Store the extracted node number
        int u = minHeapNode->val;
        dist[u] = minHeapNode->dist;

        // Traverse through all the adjacent vertices of the extracted
        // vertex 'u' and update their distance values
        Node *temp_node = graph->head[u];
        while (temp_node != nullptr)
        {
            int v = temp_node->val;

            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (minHeap->isInMinHeap(v) &&
                (dist[u] != INT_MAX) && (temp_node->weight + dist[u] < dist[v]))
            {
                dist[v] = dist[u] + temp_node->weight;

                // update distance value in minHeap also
                minHeap->decreaseKey(v, dist[v]);
            }

            temp_node = temp_node->next;
        }
    }

    printArr(dist, V);
}

int main()
{
    int V = 6;

    // GfG Graph (Undirected)
    // Edge edges[] = {{0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7}};

    // Abdul Bari Graph
    Edge edges[] = {{0, 1, 2}, {1, 3, 7}, {3, 5, 1}, {0, 2, 4}, {2, 4, 3}, {4, 5, 5}, {1, 2, 1}, {4, 3, 2}};

    int e = sizeof(edges) / sizeof(edges[0]);
    Graph graph(edges, e, V);

    Dijkstra(&graph, 0);
}