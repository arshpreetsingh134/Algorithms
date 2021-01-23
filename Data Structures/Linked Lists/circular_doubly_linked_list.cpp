// Circular Doubly LinkedList using Sentinel Node

#include <iostream>
#include <limits.h>
using namespace std;

// Node Data Structure
struct Node
{
    int val;
    Node *prev;
    Node *next;

    Node()
    {
        val = INT_MAX;
        prev = NULL;
        next = NULL;
    }

    Node(Node *prev, int val, Node *next)
    {
        this->val = val;
        this->prev = prev;
        this->next = next;
    }
};

// Circular Doubly LinkedList Class
class CDList
{
    Node *head; // Pointer to Sentinel Value
    Node *sent; // Sentinel Value

public:
    CDList()
    {
        // Sentinel Node
        sent = new Node();
        head = sent;
    }

    // Search for given key until found and return NODE else, return NULL
    Node *Search(int key)
    {
        Node *x = head->next;   // Not head because we've used Sentinel.
        while (x != NULL && x->val != key)
        {
            x = x->next;
        }
        return x;
    }

// Insert Node at the first position
    void Insert(int key)
    {
        Node* x = new Node(head, key, head->next);

        // If LL already has a node
        if(head->next!=NULL)
            head->next->prev = x;
        else                
            // If this is the First Node to be inserted
            // Point the 'prev' of Sentinel to this node
            head->prev = x;

        head->next = x;
    }

// Delete Node, given the key of the Node
    void Delete(int key)
    {
        Node *x = Search(key);

        if (x == NULL)
            return;

        // If x is not Head
        if (x->prev->val != head->val)
            x->prev->next = x->next;

        // If x is head
        else
            head->next = x->next;

        // If x is not tail
        if (x->next->val != head->val)
            x->next->prev = x->prev;

        //If x is tail
        else
            x->prev->next = head;

        delete x;
    }

    void printLL()
    {
        Node* temp = head->next;
        while(temp->val!=head->val)
        {
            cout<<temp->val<<" ";
            temp = temp->next;
        }
    }

};

int main()
{
    CDList *cd = new CDList();

    cd->Insert(26);
    cd->Insert(34);
    cd->Insert(48);
    cd->Insert(66);
    cd->Delete(48);
    cd->Insert(99);
    cd->Insert(20);
    cd->Delete(20);

    cd->printLL();
}