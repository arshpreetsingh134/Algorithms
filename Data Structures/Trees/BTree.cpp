// Implementation of a B-Tree (O(nlog(n)) for all operations)

#include <iostream>
using namespace std;

// A B-Tree Node
class Node
{
    int n;        // No. of keys currently in the Node
    int *keys;    // An array of keys inside the node
    Node **child; // An array of pointers representing child nodes

    int d;       // Min Degree (no. of children)-- This ensures that the no. of keys in the Node will always be odd
    bool isLeaf; // To keep track of leaves and non-leaves
    bool isFull; // Is the Node full or there's still space available?

public:
    Node(int d, bool isLeaf)
    {
        this->d = d;
        this->isLeaf = isLeaf;

        // Allocating memory to keys and children of the Node
        keys = new int[(2 * d - 1)]; // ∵ Maximum key nodes for a given degree = 2d-1

        child = new Node *[(2 * d)];
        for (int i = 0; i < 2 * d; i++)
        {
            child[i] = nullptr;
        }

        n = 0;          // By default, currently there are no keys in this Node
        isFull = false; // and the Node is empty
    }

    // Utility function to split the child of the current Node into 2, with an
    // assumption that this function will only be called if the child is full.
    void splitChild(int c, Node *y)
    {
        // Create a new node which will store d-1 keys
        Node *z = new Node(y->d, y->isLeaf);

        // Update the number of current keys in z
        z->n = z->d - 1;

        // Copy the last (d-1) keys to z
        for (int i = 0; i < d - 1; i++)
            z->keys[i] = y->keys[i + d];

        // Copy the last d children of y to z
        if (!y->isLeaf)
        {
            for (int i = 0; i < d; i++)
                z->child[i] = y->child[i + d];
        }

        // Reduce the no. of keys in y
        y->n = d - 1;

        // Since this Node is going to have a new child,
        // make space for the new one by shifting all greater
        // children one space ahead(Recall, n keys => n+1 children)
        for (int i = n; i >= c + 1; i--)
            child[i + 1] = child[i];

        // Link the new child to the current Node
        child[c + 1] = z;

        // A key of y will move to this node. Find the location of
        // the new key and move all greater keys one space ahead
        for (int i = n - 1; i >= c; i--)
            keys[i + 1] = keys[i];

        // Copy the middle key of y to this node
        keys[c] = y->keys[d - 1];

        // Increment count of keys in this node
        n++;

        // After inserting the value, check if the Node is full already
        if (n == 2 * d - 1)
            isFull = true;
    }

    // Utility function to insert a new key into the node, with an assumption
    // that this function will only be called if the node is currently not full
    void insertKey(int value)
    {
        int i = n - 1; // Start from the rightmost key

        // There are 2 cases :-

        // CASE 1: If the Node is a leaf
        if (isLeaf)
        {
            while (i >= 0 && keys[i] > value)
            {
                keys[i + 1] = keys[i]; // Keep shifting the larger keys by 1
                i--;
            }

            keys[i + 1] = value; // Fit the current value
            n++;
        }

        // CASE 2: If the Node is a non-leaf
        else
        {
            // Find the child which is going to accept the key
            while (i >= 0 && keys[i] > value)
                i--;

            if (child[i + 1]->isFull)
            {
                // If the child is full, split it into 2
                splitChild(i + 1, child[i + 1]);

                // After split, if the current value is even greater than
                // the newly inserted key in the Node (i.e., middle key of the
                // child node, then shift towards the next child of the current node
                if (keys[i + 1] < value)
                    i++;
            }

            // Call the function recursively for the following child node
            child[i + 1]->insertKey(value);
        }
    }

    // Function to search key k in subtree rooted with this node
    Node *search(int k)
    {
        int i = 0;
        while (i < n && k > keys[i])
            i++;

        // If the found key is equal to k, return this node
        if (keys[i] == k)
            return this;

        // If the key is not found here and this is a leaf node,
        // return NULL
        if (isLeaf)
            return nullptr;

        // Else go to the appropriate child
        return child[i]->search(k);
    }

    // Function to traverse all the nodes in a subtree rooted with this one
    void traverse()
    {
        int i;

        // There are n keys and n+1 children, traverse through n keys
        // and first n children (excluding the last one)
        for (i = 0; i < n; i++)
        {
            // If this is not a leaf, then traverse the subtree at 'i'
            // before printing key[i]
            if (!isLeaf)
                child[i]->traverse();
            cout << " " << keys[i];
        }

        // Print the subtree rooted with last child
        if (!isLeaf)
            child[i]->traverse();
    }

    // Make BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;
};

class BTree
{
    Node *root; // Pointer to Root Node
    int d;      // Minimum Degree

public:
    BTree(int d)
    {
        root = nullptr;
        this->d = d;
    }

    // Function to traverse the tree
    void traverse()
    {
        if (root)
            root->traverse();
    }

    // Function to search for a given key in this tree
    Node *search(int key)
    {
        return (root == nullptr) ? nullptr : root->search(key);
    }

    // Main function that inserts a new key inside the tree
    void insert(int val)
    {
        // If tree is empty
        if (!root)
        {
            // Allocate memory for the new root
            root = new Node(d, true);
            root->keys[0] = val;
            root->n = 1;
        }

        // If tree is not empty
        else
        {
            // If the node is full, then tree grows in height
            if (root->isFull)
            {
                // Make a new root
                Node *new_root = new Node(d, false);

                // Make old root as the child of new root
                new_root->child[0] = root;

                // Split the new root and move 1 key to the new root
                new_root->splitChild(0, root);

                // New root will have 2 children after splitting. So we
                // have to decide, in which child will the value be inserted
                int i = 0;

                if (val > new_root->keys[0])
                    i++;

                new_root->child[i]->insertKey(val);

                // Change the root
                root = new_root;
            }

            // If the node is not full
            else
            {
                root->insertKey(val);
            }
        }
    }
};

int main()
{
    BTree *bt = new BTree(4);

    bt->insert(10);
    bt->insert(20);
    bt->insert(5);
    bt->insert(6);
    bt->insert(12);
    bt->insert(30);
    bt->insert(7);
    bt->insert(17);

    cout << "Traversal of the constucted tree is: ";
    bt->traverse();

    int k = 6;
    (bt->search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    k = 15;
    (bt->search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    cout<<endl;
}