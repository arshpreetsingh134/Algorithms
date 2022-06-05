// Implementation of Huffman Coding using Priority Queue DS (O(n.log(n)))

#include <iostream>
#include <queue>
#include <limits.h>
#define ll long long int
using namespace std;

class Node
{
public:
    int val;
    ll freq;

    Node *left;
    Node *right;

    // Node(int val, int freq, Node* left, Node* right): val(val), freq(freq), left(left), right(right) {}

    Node(int val, ll freq)
    {
        this->val = val;
        this->freq = freq;
        this->left = this->right = nullptr;
    }
};

// Custom Comparator: Defining priority based on frequency
struct compareFreq
{
    bool operator()(Node *p1, Node *p2)
    {
        return p1->freq > p2->freq;
    }
};

// Check if the given node is a leaf, i.e., it has neither left node nor right
bool isLeaf(Node *root)
{
    return !(root->left) && !(root->right);
}

// Function to generate a Huffman Encoding Tree
Node *generateTree(priority_queue<Node *, vector<Node *>, compareFreq> &pq)
{
    // Choose the 2 minimum-value nodes from the Queue until there is only one
    // node left
    int count = 0;
    while (pq.size() != 1)
    {
        // Fetch the 2 nodes having least frequency and pop them
        // from the Priority Queue
        Node *n1 = pq.top();
        pq.pop();
        Node *n2 = pq.top();
        pq.pop();

        ll sum_freq = n1->freq + n2->freq;

        // Here, we are only concerned with the combined frequency of the 2 nodes,
        // so value doesn't really matter
        Node *node = new Node('g' + count, sum_freq);

        // Store the individual nodes to the combined node
        node->left = n1;
        node->right = n2;

        // Push the combined node to the Priority Queue
        pq.push(node);
        count++;
    }

    return pq.top();
}

// Print the respective codes for the Huffman Tree leaf values
void printCodes(Node *root, vector<bool> &codes, int top, int &min, int &max)
{
    if (root->left)
    {
        codes[top] = 0;
        printCodes(root->left, codes, top + 1, min, max);
    }

    if (root->right)
    {
        codes[top] = 1;
        printCodes(root->right, codes, top + 1, min, max);
    }

    if (isLeaf(root))
    {
        cout << root->val << " --> ";

        for (int i = 0; i < top; i++)
            cout << codes[i];
        cout << " size: " << top;

        if (min > top)
            min = top;

        if (max < top)
            max = top;

        cout << endl;
    }
}

// Given the data and their respective frequencies, generate the encoding for each
// data
void Huffman(vector<int> val, vector<ll> freq)
{
    int N = val.size();
    priority_queue<Node *, vector<Node *>, compareFreq> pq;

    // Populating the Priority Queue (for individual nodes)
    for (int i = 0; i < N; i++)
    {
        Node *temp_node = new Node(val[i], freq[i]);
        pq.push(temp_node);
    }

    Node *root = generateTree(pq);

    vector<bool> arr(N, 0);
    int top = 0;

    int min = INT_MAX;
    int max = INT_MIN;
    printCodes(root, arr, top, min, max);

    cout << "\nMinimum Size of encoding: " << min;
    cout << "\nMaximum Size of encoding: " << max;
}

int main()
{
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("txt/huffman.txt", "r", stdin);
#endif

    cout << "Hello Stanford!\n"
         << endl;

    int N;
    cin >> N;

    ll frequency;

    vector<int> val;
    vector<ll> freq;

    for (int i = 0; i < N; i++)
    {
        int data = i + 1;
        val.push_back(data);
    }

    for (int i = 0; i < N; i++)
    {
        cin >> frequency;
        freq.push_back(frequency);
    }

    Huffman(val, freq);
    cout << endl;
}
