// Implementation of a Binary Search Tree (BST)
// All operations: O(height)

#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>

class BST
{
    // Internal node data type containing node
    // references and the actual node data
    class Node
    {
    public:
        T data;
        Node *left;
        Node *right;

        // Default Constructor
        Node() : data(0), left(nullptr), right(nullptr) {}

        // Parameterized Constructor
        Node(T data, Node *left = nullptr, Node *right = nullptr)
        {
            this->data = data;
            this->left = left;
            this->right = right;
        }
    };

    // For keeping track of BST Size
    int nodeCount;

    // This BST is a rooted tree so we maintain a handle on the root node
    Node *root = NULL;

    // Check if the Binary Tree is empty
    bool isEmpty()
    {
        return nodeCount == 0;
    }

    // Returns the MINIMUM KEY Node of the Binary Tree
    Node *findMin(Node *node)
    {
        while (node->left)
        {
            node = node->left;
        }
        return node;
    }

    // Returns the MAXIMUM KEY Node of the Binary Tree
    Node *findMax(Node *node)
    {
        while (node->right)
        {
            node = node->right;
        }
        return node;
    }

    // Private method to recursively add a value in the binary tree
    Node *addNode(Node *node, T elem)
    {
        // If tree empty, make a new node and insert it to the tree
        if (node == nullptr)
            node = new Node(elem);

        else
        {
            // Pick a subtree to insert element
            if (elem < node->data)
                node->left = addNode(node->left, elem);
            else
                node->right = addNode(node->right, elem);
        }

        return node;
    }

    // Private method to recursively delete a value in the binary tree
    Node *deleteNode(Node *node, T elem)
    {
        if (node == nullptr)
            return NULL;

        // Dig into the left subtree if the elem is less than
        // the root value
        if (elem < node->data)
            return node->left = deleteNode(node->left, elem);

        // Dig into the right subtree if the elem is more than
        // the root value
        else if (elem > node->data)
            return node->right = deleteNode(node->right, elem);

        // Found the node we wish to delete
        else
        {
            // There are 3 cases here...

            // CASE-1: This is the case with only a right subtree or
            // no subtree at all. In this situation just swap the node
            // we wish to remove with its right child.
            if (node->left == NULL)
                return node->right;

            // CASE-2: This is the case with only a left subtree or
            // no subtree at all. In this situation just swap the node
            // we wish to remove with its left child.
            else if (node->right == NULL)
                return node->left;

            // CASE-3: When removing a node from a binary tree with two links,
            // the successor of the node being removed can either be the largest
            // value in the left subtree (predecessor) or the smallest value in the right
            // subtree (successor). In this implementation I have decided to find the
            // largest value in the left subtree (predecessor) which can be found by
            // traversing as far left as possible in the right subtree.
            else
            {
                // Find the maximum in left subtree (predecessor)
                Node *temp = findMax(node->left);

                // Swap the data
                node->data = temp->data;

                // Go into the right subtree and remove the leftmost node we
                // found and swapped data with. This prevents us from having
                // two nodes in our tree with the same value.
                node->left = deleteNode(node->left, temp->data);

                // If instead we wanted to find the largest node in the left
                // subtree as opposed to smallest node in the right subtree
                // here is what we would do:-
                // Node temp = findMin(node.right);
                // node.data = temp.data;
                // node.right = deleteNode(node.right, tmp.data);

                return node;
            }
        }
    }

    // Height of the tree
    int height(Node *node)
    {
        if (node == NULL)
            return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    // In-order Traversal of the BST
    void traverse(Node *root)
    {
        if (root == NULL)
            return;

        traverse(root->left);
        cout << root->data << " ";
        traverse(root->right);
    }

    // Return the pointer to the node where the value is present
    Node *find(Node *t, int x)
    {
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            return find(t->left, x);
        else if (x > t->data)
            return find(t->right, x);
        else
            return t;
    }

public:
    // Recursive method to find a key in the tree
    // returns True if key found in the tree, else False
    bool searchNode(Node *node, T key)
    {
        // Base Case: Reached Bottom, Value not Found!
        if (!node)
            return false;

        // Dig into the left subtree because the value we're
        // looking for is smaller than the current value
        else if (key < node->data)
            return searchNode(node->left, key);

        // Dig into the right subtree because the value we're
        // looking for is greater than the current value
        else if (key > node->data)
            return searchNode(node->right, key);

        // We found the value we were looking for
        else
            return true;
    }

    void search(T key)
    {
        if(searchNode(root, key))
            cout<<"Node found!";
        else
            cout<<"Node not found";     
    }

    // INSERT an element to this binary tree. Returns
    // true if we successfully performed an insertion
    bool addNode(T elem)
    {
        // Check if the value already exists in the binary
        // tree (to handle duplicates)
        if (searchNode(root, elem))
            return false;

        // Otherwise add this element to the binary tree
        else
        {
            root = addNode(root, elem);
            nodeCount++;
            return true;
        }
    }

    // DELETE a key from this binary tree if it exists, O(n)
    bool deleteNode(T elem)
    {
        // If elem is already present, remove it
        if (searchNode(root, elem))
        {
            root = deleteNode(root, elem);
            nodeCount--;
            return true;
        }
        return false;
    }

    // Compute the height of the tree
    int height()
    {
        return height(root);
    }

    void traverse()
    {
        traverse(root);
    }
};

int main()
{
    BST<int> *obj = new BST<int>();

    obj->addNode(20);
    obj->addNode(25);
    obj->addNode(15);
    obj->addNode(10);
    obj->addNode(30);

    obj->traverse();
    cout<<endl;
    obj->deleteNode(20);

    obj->traverse();
    cout<<endl;
    obj->deleteNode(25);

    obj->traverse();
    cout<<endl;
    obj->deleteNode(30);

    obj->traverse();
    cout<<endl;

    obj->search(35);
    cout<<endl;
}