// Implementation of XOR-Doubly_LinkedList, in which instead of using 2 pointers *prev* & *next*,
// we use a single pointer *x_np* which is equal to (address(prev) XOR address(next))

#include <iostream>
using namespace std;

// Node Data Structure of a
// memory-efficient linkedlist
struct Node
{
    int data;
    Node *x_np; // XOR of prev and next node

    Node(int data, Node *x_np)
    {
        this->data = data;
        this->x_np = x_np;
    }
};

class LinkedList
{
    Node *head;

    // Returns XORed value of the node addresses
    Node *XOR(Node *prev, Node *next)
    {
        return (Node *)(((unsigned long) prev) ^ ((unsigned long) next));
    }

public:
    LinkedList()
    {
        head = NULL;
    }

    // Search Node, given key
    Node* searchNode(int key)
    {
        Node* x = head;
        Node* prev = NULL;
        Node* next;

        while(x!=NULL && x->data!=key)
        {
            next = XOR(prev, x->x_np);
            prev = x;
            x = next;
        }
        return x;
    }

    // Insert a node at the beginning of the XORed LinkedList
    void insertNode(int data)
    {
        Node *new_node = new Node(data, head);

        // Since new node is being inserted at the
        // beginning, x_np of new node will always be
        // XOR of current head and NULL, which is the
        // current head itself

        // If linked list is not empty, then x_np of
        // current head node (2nd Node) will be XOR of 
        // new node and node next to current head
        if(head!=NULL)
        {
            head->x_np = XOR(new_node, head->x_np);
        }

        // Update head
        head = new_node;
    }

    void deleteNode(int key)
    {
        Node *x = head;
        Node *prev = NULL;
        Node *next;

        while (x != NULL && x->data != key)
        {
            next = XOR(prev, x->x_np);
            prev = x;
            x = next;
        }

        if(x==NULL)
            return;

        // If x is at tail
        if(XOR(prev, x->x_np)==NULL)
        {
            prev->x_np = XOR(prev->x_np,x);
        }

        // If x is at head
        else if(prev==NULL)
        {
            Node *next_node = head->x_np;
            next_node->x_np = XOR(x, next_node->x_np);
            head = next_node;
            return;        
        }

        // Intermediary Node
        else
        {
            Node *next_node = XOR(x->x_np, prev);
            prev->x_np = XOR(XOR(prev->x_np, x), next_node);
            next_node->x_np = XOR(prev, XOR(next_node->x_np, x));
        }

        delete x;
    }

    void printList()
    {
        Node *curr = head;
        Node *prev = NULL;
        Node* next;

        while(curr!=NULL)
        {
            cout<<curr->data<<" ";

            // Get address of next node: curr->npx is
            // next^prev, so curr->npx^prev will be
            // next^prev^prev which is next
            next = XOR(prev, curr->x_np);

            // Update prev and next for next iteration
            prev = curr;
            curr = next;
        }
        cout<<endl;
    }
};

int main()
{
    LinkedList *obj = new LinkedList();
    obj->insertNode(20);
    obj->insertNode(60);
    obj->insertNode(80);
    obj->insertNode(90);

    obj->printList();

    obj->deleteNode(90);

    obj->insertNode(100);

    obj->printList();
}
