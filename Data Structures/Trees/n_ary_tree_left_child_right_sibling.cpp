// Implementation of an n-ary tree using Left-Child Right_Sibling Representation
// This new transformation not only removes the need of advance knowledge of the
// number of children a node has, but also limits the number of references to a 
// maximum of two, thereby making it so much easier to code.
#include<iostream>
using namespace std;

struct Node
{
    char data;
    Node* child;     // Representing parent-child relationship
    Node* sibling;   // Representing sibling-sibling relationship

    Node(char data)
    {
        this->data = data;
        this->child = NULL;
        this->sibling = NULL;
    }
};

// Adding a sibling to the list starting with root
Node* addSibling(Node* root, char data)
{
    if(root==NULL)
        return NULL;
    
    while(root->sibling)
        root = root->sibling;
    
    root->sibling = new Node(data);
    return root->sibling;
}

// Add child node to the root
Node* addChild(Node* root, char data)
{
    if(root==NULL)
        return NULL;

    if(root->child)
        return addSibling(root->child, data);
    
    root->child = new Node(data);
    return root->child;
}

// Level-order Traversal of the tree
void traverseTree(Node* root)
{
    if(root==NULL)
        return;

    while(root)
    {
        cout<<root->data<<" ";
        if(root->child)
            traverseTree(root->child);
        root = root->sibling;
    }
}

int main()
{
    Node *root = new Node('A');
    Node *r1 = addChild(root, 'B');
    Node *r2 = addChild(root, 'C');
    Node *r3 = addChild(root, 'D');
    Node *r4 = addChild(root, 'E');

    Node *r5 = addChild(r2, 'F');
    Node *r6 = addChild(r2, 'G');

    Node *r7 = addChild(r3, 'H');
    Node *r8 = addChild(r3, 'I');
    Node *r9 = addChild(r3, 'J');

    traverseTree(root);
}

