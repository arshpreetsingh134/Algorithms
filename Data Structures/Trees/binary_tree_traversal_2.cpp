// Binary Tree Traversal in constant space (outside the root) and linear time
#include <iostream>
#define MAX_SIZE 10
using namespace std;

int keys[MAX_SIZE];
int cnt = 0;

struct Node
{
    int val;
    Node *parent;
    Node *left;
    Node *right;

    Node(int val)
    {
        this->val = val;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

void store(int key)
{
    keys[cnt++] = key;
}

void printTree(Node* root)
{
    Node* prev = nullptr;

    while(root)
    {
        if(prev == root->parent)
        {
            store(root->val);

            prev = root;
            root = root->left ? root->left : 
                   root->right ? root->right : 
                   root->parent;
        }

        else if(prev == root->left && root->right)
        {
            prev = root;
            root= root->right;
        }

        else
        {
            prev = root;
            root = root->parent;
        }
    }
}

int main()
{
    struct Node *root = new Node(5);
    root->left = new Node(4);
    root->right = new Node(6);
    root->parent = NULL;
    root->left->parent = root;
    root->right->parent = root;

    root->left->left = new Node(10);
    root->left->left->parent = root->left;
    root->left->right = new Node(12);
    root->left->right->parent = root->left;

    root->right->left = new Node(15);
    root->right->left->parent = root->right;
    root->right->right = new Node(20);
    root->right->right->parent = root->right;

    printTree(root);

    for (int i = 0; i < 7; i++)
        cout << keys[i] << " ";
}