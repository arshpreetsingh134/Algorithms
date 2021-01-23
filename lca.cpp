// Difference between odd and even levels of a tree....

#include<iostream>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
};

Node* newNode(int data) 
{ 
    Node* temp = new Node(); 
    temp->key = data; 
    temp->left = temp->right = NULL; 
    return temp; 
} 

int findDiff(Node* rootNode){

    if (!rootNode) 
        return 0; 

    queue<Node*> record;
    record.push(rootNode);

    int level=-1;
    int odd=0, even=0;

    while(!record.empty()){
        int size= record.size();
        level+=1;

    while(size>0){
        Node* temp = record.front();
        record.pop();
        size--;
    
        if(level%2==0)
            even=even+temp->key;
        else
            odd=odd+temp->key;

        if(temp->left !=NULL)
            record.push(temp->left);
        if(temp->right !=NULL)
            record.push(temp->right);
    }

}
return (even-odd);
} 

int main(){
    Node* root = newNode(5); 
    root->left = newNode(2); 
    root->right = newNode(6); 
    root->left->left = newNode(1); 
    root->left->right = newNode(4); 
    root->left->right->left = newNode(3); 
    root->right->right = newNode(8); 
    root->right->right->right = newNode(9); 
    root->right->right->left = newNode(7); 

    cout<<"Difference is: "<<findDiff(root)<<endl;

}