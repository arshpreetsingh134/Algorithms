#include <iostream>
#include<vector>

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

Node *newNode(int key)
{
    Node *node = new Node;

    node->data = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Finds the path from root node to given root of the tree, Stores the 
// path in a vector path[], returns true if path exists otherwise false 

bool lcapath(Node *root, vector<int> &arr, int key)
{
    if(root==NULL)
        return false;

    arr.push_back(root->data);

    if(root->data==key)
        return true;

    if((root->left && lcapath(root->left, arr, key)) || (root->right && lcapath(root->right, arr, key))){
        return true;
    }

    arr.pop_back();  
    return false;
}

//Returns LCA if node a, b are present in the given binary tree, 
//otherwise return -1 
int findLCA(Node *root, int a, int b){
    vector<int> path1, path2;

    if ( !lcapath(root, path1, a) || !lcapath(root, path2, b)) 
        return -1;
        
    int i;
    for(i=0; i<path1.size() && i<path2.size(); i++){
        if(path1[i]!=path2[i])
            break;
    }
    return path1[i-1];
} 

int main() 
{ 
    
    Node * root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    cout<<findLCA(root, 4, 7)<<endl;
    cout<<findLCA(root, 5, 3)<<endl;

} 
