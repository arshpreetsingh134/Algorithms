#include <iostream>
using namespace std;

// A linked list node
class Node
{
public:
    int data;
    Node *next;

    Node() {}

    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

class LinkedList
{
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    Node *getHead()
    {
        return head;
    }

    // Inserts a new node on the front of the
    // list.
    void insertNode(int new_data)
    {
        Node *new_node = new Node();
        new_node->data = new_data;
        new_node->next = head;
        head = new_node;
    }

    int ll_length()
    {
        Node* temp = head;
        int count = 0;
        while(temp!=NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

// Insert a node before the Linked List head node
Node* insertBefore(Node *node, int data)
{
    Node* temp = new Node(data, nullptr);
    if(node!=NULL)
        temp->next = node;
    return temp;
}

Node* padList(Node* node, int pad)
{
    for(int i=0; i<pad; i++)
        node = insertBefore(node, 0);
    return node;
}

// Wrapper Class enclosing result as well as carry
class PartialSum
{
    public:
    Node* result;
    int carry;

    PartialSum(Node* result, int carry)
    {
        this->result = result;
        this->carry = carry;
    }
};

PartialSum *returnResultHelper(Node *l1, Node *l2)
{
    // Base Case: If both lists are empty or end nodes are NULL
    if(l1==NULL && l2==NULL)
    {
        PartialSum* sum = new PartialSum(nullptr, 0);
        return sum;
    }

    // Add smaller digits recursively
    PartialSum* sum = returnResultHelper(l1->next, l2->next); 

    // Add carry to current digit sum
    int val =  sum->carry + l1->data + l2->data;

    // Insert sum of current digits in the running 'result' list
    Node* temp = insertBefore(sum->result, val%10);

    // Return sum so far and the carry value
    sum->result = temp;
    sum->carry = val/10;

    return sum;
}

Node *returnResult(LinkedList *l1, LinkedList *l2)
{
    Node* ll1 = l1->getHead();
    Node* ll2 = l2->getHead();

    int len1 = l1->ll_length();
    int len2 = l2->ll_length();

    // Pad the shorter list with 0s
    if(len1>len2)
        ll2 = padList(ll2, len1-len2);
    else if(len2>len1)
        ll1 = padList(ll1, len1-len2);

    PartialSum *p = returnResultHelper(ll1, ll2);

    // If there is a carry value left over, add it at the front of result, 
    // or return the linked list
    if(p->carry == 0)
        return p->result;
    else
    {
        Node* temp = insertBefore(p->result, p->carry);
        return temp;
    }
}

// Print List
void printList(Node *temp)
{
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    LinkedList *l1 = new LinkedList();
    LinkedList *l2 = new LinkedList();

    l1->insertNode(9);
    l1->insertNode(7);
    l1->insertNode(8);
    l1->insertNode(7);

    l2->insertNode(8);
    l2->insertNode(6);
    l2->insertNode(5);

    cout << "Linked Lists are:- \n";
    printList(l1->getHead());
    printList(l2->getHead());

    Node *result = returnResult(l1, l2);
    cout << "Sum of two numbers is: ";
    printList(result);
}