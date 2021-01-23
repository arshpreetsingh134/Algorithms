// Binary Search Traversal using explicitly-defined Stack

#include <iostream>
#define MAX_SIZE 10
using namespace std;

int keys[MAX_SIZE];
int cnt = 0;

struct Node
{
    int val;
    Node *left;
    Node *right;

    Node(int val)
    {
        this->val = val;
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
    Node* stack[MAX_SIZE];
    int count = 0;

    stack[count++] = root;

    while(count)
    {
        root = stack[--count];
        store(root->val);

        if(root->right)
            stack[count++] = root->right;
        if(root->left)
            stack[count++] = root->left;
    }
}

int main()
{
    struct Node *root = new Node(5);
    root->left = new Node(4);
    root->right = new Node(6);

    root->left->left = new Node(10);
    root->left->right = new Node(12);

    root->right->left = new Node(15);
    root->right->right = new Node(20);

    printTree(root);

    for(int i=0; i<7; i++)
        cout<<keys[i]<<" ";
}