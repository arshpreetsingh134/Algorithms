// Karger's Algorithm, 1993- Contraction Algorithm for Minimum Cut Problem of a graph (Graph Partitioning)
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

// DS for representing an edge
struct Edge
{
    int src;
    int dest;
};

// DS for representing a graph
struct Graph
{
    // No of vertices & edges inside the graph
    int V;
    //int E;

    // A dynamic array for keeping track of all the edges inside the undirected graph
    vector<Edge> edge;
};

// DS for representing a subset for Union-Find
struct subset
{
    int parent;
    int rank;
};

// ******************* Union-Find Operations ******************* //

// A utility function to find set of an element i
// (uses path compression technique)
int Find(vector<subset> &subsets, int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = Find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// Union of 2 subsets x and y
void Union(vector<subset> &subsets, int x, int y)
{
    int X = Find(subsets, x);
    int Y = Find(subsets, y);

    // Unite 2 subsets according to their respective ranks
    if (subsets[X].rank < subsets[Y].rank)
        subsets[X].parent = Y;
    else if (subsets[X].rank > subsets[Y].rank)
        subsets[Y].parent = X;

    else
    {
        // If ranks of both the subsets are equal,
        // then make one as root and increent its rank by 1
        subsets[Y].parent = X;
        subsets[X].rank++;
    }
}

// ******************* ******* ******************* //

// Subroutine for the implementation of Karger's Algorithm
int Karger(struct Graph *graph)
{
    int V = graph->V;
    int E = graph->edge.size();

    // Create V subsets with single elements (Initially there are V vertices in the contracted graph)
    vector<subset> subsets(V);

    for (int v = 0; v < V; v++)
    {
        //cout<<endl<<v;
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int vertices = V; // for contracted graph

    while (vertices > 2)
    {
        // Choose an edge uniformly at random
        srand((unsigned)time(0));
        int random_edge = (rand() % E);

        // Find the 2 vertices (or sets) that are joined by this random_edge
        int sub1 = Find(subsets, graph->edge[random_edge].src);
        int sub2 = Find(subsets, graph->edge[random_edge].dest);

        // If 2 corners belong to the same subset (i.e., the 2 vertices have already been contracted),
        // so no point choosing this edge all over again
        if (sub1 == sub2)
            continue;
        else
        {
            // Contract this edge
            vertices--;
            //cout << "\nContracting edge " << graph->edge[random_edge].src << "-" << graph->edge[random_edge].dest;
            Union(subsets, sub1, sub2);
        }
    }

    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int count = 0;
    for (int i = 0; i < V; i++)
    {
        int sub1 = Find(subsets, graph->edge[i].src);
        int sub2 = Find(subsets, graph->edge[i].dest);
        if (sub1 != sub2)
            count++;
    }
    return count;
}

// For initializing a graph with given V
struct Graph *createGraph(int V)
{
    Graph *my_graph = new Graph;
    my_graph->V = V;
    //my_graph->E = E;

    //my_graph->edge = new Edge[E];
    return my_graph;
}

// For creating an edge, given source and destination
void createEdge(struct Graph *graph, int src, int dest)
{
    struct Edge *new_edge = new Edge;

    new_edge->src = src;
    new_edge->dest = dest;

    graph->edge.push_back(*new_edge);
}

int main()
{
    // Enter the number of edges and vertices in the graph
    int V = 200;

    struct Graph *graph = createGraph(V);

    ifstream inFile("kargerMinCut.txt");
    string line;
    //ofstream outFile("b.txt");

    while (getline(inFile, line))
    {
        vector<int> temp;
        //cout << line << endl;

        // Returns first token
        char char_array[line.length() + 1];
        strcpy(char_array, line.c_str());

        char *token = strtok(char_array, "	");

        // Keep printing tokens while one of the
        // delimiters present in str[].
        while (token != NULL)
        {
            int num;
            sscanf(token, "%d", &num);
            temp.push_back(num);

            token = strtok(NULL, "	");
        }

        for (int i = 1; i < temp.size(); i++)
            createEdge(graph, temp[0], temp[i]);
    }

    int E = graph->edge.size();

    // for (auto &i : graph->edge)
    //     cout << i.src << " " << i.dest << endl;

    cout << "\nCut found by Karger's randomized algorithm is: " << Karger(graph);
    
}