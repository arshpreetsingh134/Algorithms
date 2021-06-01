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
    bool isLeaf; // To keep track of a node being a leaf or not
    bool isFull; // Is the Node full or there's still space available?

public:
    Node(int d, bool isLeaf)
    {
        this->d = d;
        this->isLeaf = isLeaf;

        // Allocating memory to keys and children of the Node
        keys = new int[(2 * d - 1)]; // ∵ Maximum key nodes for a given degree d = 2d-1

        child = new Node *[(2 * d)]; // ∵ Maximum children for a given degree d = 2d

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

        // Since "this" Node is going to have a new child,
        // make space for the new one by shifting all greater
        // children one space ahead (Recall, n keys => n+1 children)
        for (int i = n; i >= c + 1; i--)
            child[i + 1] = child[i];

        // Link the new child to "this" Node
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
                // child node), then shift towards the next child of the current node
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

    // Utility Function that returns the index of first key greater than or
    // equal to k
    int findKey(int k)
    {
        int i = 0;
        while (i < n && keys[i] < k)
            i++;
        return i;
    }

    // Utility-2 Function to find the predecessor of key[i], which is present
    // in the subtree rooted at "this" node (i.e. key in the left subtree whose
    // value is just less than the current key)
    int findPred(int i)
    {
        Node *left_child = child[i];

        // Keep moving to the rightmost node under the left subtree of "this"
        // root until we reach a leaf...
        while (!left_child->isLeaf)
            left_child = left_child->child[left_child->n];

        // Return the rightmost key of the last subtree
        return left_child->keys[(left_child->n) - 1];
    }

    // Utility-2 Function to find the successor of key[i] present in the
    // subtree rooted at "this" node (i.e. key in the right subtree whose
    // value is just greater than the current key)
    int findSucc(int i)
    {
        Node *right_child = child[i + 1];

        // Keep moving to the leftmost node under the right subtree of "this"
        // root until we reach a leaf...
        while (!right_child->isLeaf)
            right_child = right_child->child[0];

        // Return the leftmost key of the last subtree
        return right_child->keys[0];
    }

    // Utility-2 Function to merge child[i], key[i] and child[i+1],
    // and then free the child[i+1]
    void merge(int i)
    {
        Node *Child = child[i];       // The OG Child Node where merge takes place
        Node *Sibling = child[i + 1]; // The next child w.r.t the current key
                                      // This will be freed in the end

        // Pull a key from "this" node and insert it in child[i]
        Child->keys[d - 1] = keys[i];

        // Copy all keys from child[i+1] to child[i]
        for (int j = 0; j < Sibling->n; j++)
            Child->keys[d + j] = Sibling->keys[j];

        // Copy the child pointers from child[i+1] to child[i]
        if (!Child->isLeaf)
        {
            for (int j = 0; j <= Sibling->n; j++)
            {
                Child->child[d + j] = Sibling->child[j];
            }
        }

        // Moving all keys after i in the current node one step to the left
        // to fill the gap created by pulling out keys[i]
        for (int j = i + 1; j < n; j++)
            keys[j - 1] = keys[j];

        // Similarly, moving child pointers one step to the left
        for (int j = i + 2; j <= n; j++)
            child[j - 1] = child[j];

        // Updating the key count of the child and the current node
        Child->n = 2 * d - 1;
        n--;

        // Freeing the memory occupied by child[i+1]
        delete (Sibling);
    }

    // Utility Function to remove the key at a given index from a Leaf Node
    void removeFromLeaf(int i)
    {
        // Shift all keys after the i-th index one place to the left
        for (int j = i + 1; j < n; j++)
            keys[j - 1] = keys[j];

        // Reduce the count of keys
        n--;
    }

    // Utility Function to remove the key at a given index from a Non-Leaf Node
    void removeFromNonLeaf(int i)
    {
        int k = keys[i];
        // There are 3 cases :-

        // CASE 1: If the child that precedes k (child[i]) has at least d keys,
        // find the predecessor "pred" of k in the subtree rooted at child[i].
        // Replace k by "pred". Now recursively delete "pred"
        if (child[i]->n >= d)
        {
            int pred = findPred(i);
            keys[i] = pred;
            child[i]->remove(pred);
        }

        // CASE 2: If child[i] has less than d keys, then examine child[i+1]:-
        // If the child that succeeds k (child[i+1]) has at least d keys,
        // find the successor "succ" of k in the subtree rooted at child[i+1].
        // Replace k by "succ". Now recursively delete "succ"
        else if (child[i + 1]->n >= d)
        {
            int succ = findSucc(i);
            keys[i] = succ;
            child[i + 1]->remove(succ);
        }

        // CASE 3: If both child[i] and child[i+1] have less than d keys,
        // merge both k and child[i+1] into child[i], such that child[i]
        // now contains 2d-1 keys (max keys in a node). Then recursively
        // delete k from child[i]
        else
        {
            merge(i);
            child[i]->remove(k);
        }
    }

    // Utility-2 Function to borrow a key from the previous sibling child[i-1]
    // and insert it into child[i]
    void borrowFromPrev(int i)
    {
        Node *curr = child[i];             // Current child which needs a key
        Node *prev_sibling = child[i - 1]; // Previous child from which to fetch the key

        // The last key from child[i-1] goes up to the parent and the key[i-1]
        // from the parent is inserted as the first key into child[i]. Thus,
        // sibling loses one key and child gains one. So overall, everything is
        // balanced

        // Move all keys in child[i] one step ahead (to make way for a new one)
        for (int j = curr->n - 1; j >= 0; j--)
            curr->keys[j + 1] = curr->keys[j];

        // If child[i] is not a leaf, move all its child pointers one step ahead
        // as well
        if (!curr->isLeaf)
        {
            for (int j = curr->n; j >= 0; j--)
                curr->child[j + 1] = curr->child[j];
        }

        // Setting child's first key equal to keys[i-1] from "this" node
        curr->keys[0] = keys[i - 1];

        // Setting sibling's last child as current child's first child
        if (!curr->isLeaf)
            curr->child[0] = prev_sibling->child[prev_sibling->n];

        // Moving the key from the sibling to "this" parent. This reduces
        // the number of keys in the sibling
        keys[i - 1] = prev_sibling->keys[prev_sibling->n - 1];

        // Increment number of keys in current child and decrement in prev child
        curr->n++;
        prev_sibling->n--;
    }

    // Utility-2 Function to borrow a key from the next sibling child[i+1]
    // and insert it into child[i]
    void borrowFromNext(int i)
    {
        Node *curr = child[i];             // Current child which needs a key
        Node *next_sibling = child[i + 1]; // Next child from which to fetch the key

        // The first key from child[i+1] goes up to the parent and the key[i]
        // from the parent is inserted as the last key into child[i]. Thus,
        // sibling loses one key and child gains one. So overall, everything is
        // balanced

        // Setting child's last key equal to keys[i] from "this" node
        curr->keys[curr->n] = keys[i];

        // Setting sibling's first child as current child's last child
        if (!curr->isLeaf)
            curr->child[curr->n + 1] = next_sibling->child[0];

        // Moving the first key from the sibling to "this" parent. This reduces
        // the number of keys in the sibling
        keys[i] = next_sibling->keys[0];

        // Move all keys in the sibling one step behind (because first one was removed)
        for (int j = 1; j < next_sibling->n; j++)
            next_sibling->keys[j - 1] = next_sibling->keys[j];

        // If sibling is not a leaf, move all its child pointers one step behind
        if (!next_sibling->isLeaf)
        {
            for (int j = 1; j <= next_sibling->n; j++)
                next_sibling->child[j - 1] = next_sibling->child[j];
        }

        // Increment number of keys in current child and decrement in next child
        curr->n++;
        next_sibling->n--;
    }

    // Utility function to fill the child[i] which has less than d keys
    void fill(int i)
    {
        // CASE 1: If the previous child has more than d-1 keys, borrow from that child
        if (i != 0 && child[i - 1]->n >= d)
            borrowFromPrev(i);

        // CASE 2: If the next child has more than d-1 keys, borrow from that child
        if (i != n && child[i + 1]->n >= d)
            borrowFromNext(i);

        // CASE 3: If both siblings have less than d keys, merge child[i] with its sibling
        // (if last child, merge with its prev sibling, else merge with its next sibling)
        else
        {
            if (i != n)
                merge(i);
            else
                merge(i - 1);
        }
    }

    // Function to remove the key 'k' from subtree rooted with "this" node
    void remove(int k)
    {
        // Find the index of first key greater than or equal to k
        int i = findKey(k);

        // CASE 1: If the key to be deleted is present in "this" node
        if (k == keys[i] && i < n)
        {
            // CASE 1(a): If the node is a leaf node
            if (isLeaf)
                removeFromLeaf(i);
            // CASE 1(b): If the node is a non-leaf node
            else
                removeFromNonLeaf(i);
        }

        // CASE 2: If the key to be deleted is present in the subtree rooted
        // with "this" node
        else
        {
            // If "this" node is a leaf node, then the key is not present in the tree,
            // it's obvious...
            if (isLeaf)
            {
                cout << "Key " << k << " is not present in the leaf";
                return;
            }

            // The flag indicates whether the key present in the sub-tree is rooted
            // with the last child of this node
            bool flag = ((i == n) ? true : false);

            // If the child where the key is supposed to exist has less than
            // d keys, fill that child (either from the left sibling or from
            // the right sibling, or merge both...[see fill() function])
            if (child[i]->n < d)
                fill(i);

            // If the last child has been merged, it must have merged with the previous
            // child and so we recurse on the (i-1)th child. Else, we recurse on the
            // (i)th child which now has atleast t keys
            if (flag && i > n)
                child[i - 1]->remove(k);
            else
                child[i]->remove(k);
        }
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

                // Split the old root and move 1 key to the new root
                new_root->splitChild(0, root);

                // New root will have 2 children after splitting. So we
                // have to decide, in which child will the value be inserted
                int i = 0;

                if (val > new_root->keys[0])
                    i++;

                new_root->child[i]->insertKey(val);

                // Update the new root
                root = new_root;
            }

            // If the node is not full
            else
            {
                root->insertKey(val);
            }
        }
    }

    // Function to remove a given value from the tree
    void remove(int value)
    {
        // If the B-Tree is empty
        if (!root)
        {
            cout << "\nTree is empty.";
            return;
        }

        // Call the remove() function for root
        root->remove(value);

        // If the root node has 0 keys, make its first child as the new root
        //  if it has a child, otherwise set root as NULL
        if (root->n == 0)
        {
            Node *tmp = root;
            if (root->isLeaf)
                root = nullptr;
            else
                root = root->child[0];

            // Free the old root
            delete tmp;
        }
    }
};

int main()
{
    BTree *bt = new BTree(3);

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

    bt->remove(12);

    cout << "\nTraversal of the constucted tree after removing 12 is: ";
    bt->traverse();

    bt->remove(30);

    cout << "\nTraversal of the constucted tree after removing 30 is: ";
    bt->traverse();

    int k = 6;
    (bt->search(k) != NULL) ? cout << endl
                                   << k << " is Present"
                            : cout << endl
                                   << k << " is Not Present";

    k = 15;
    (bt->search(k) != NULL) ? cout << endl
                                   << k << " is Present"
                            : cout << endl
                                   << k << " is Not Present";

    k = 12;
    (bt->search(k) != NULL) ? cout << endl
                                   << k << " is Present"
                            : cout << endl
                                   << k << " is Not Present";

    cout << endl;
}

// Traversal of the constucted tree is:  5 6 7 10 12 17 20 30
// Traversal of the constucted tree after removing 12 is:  5 6 7 10 17 20 30
// Traversal of the constucted tree after removing 30 is:  5 6 7 10 17 20
// 6 is Present
// 15 is Not Present
// 12 is Not Present