// Find the intersecting node of the 2 Linked Lists
#include <iostream>
#include <cmath>
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

    // For creating an intersection
    void insertAfter(Node *node)
    {
        if (head == NULL)
        {
            head = node;
            return;
        }

        Node *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = node;
    }

    void printList(Node *temp)
    {
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int ll_length()
    {
        Node *temp = head;
        int count = 0;
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

// Wrapper class: To keep track of the tail node and the length of LL
class Result
{
public:
    int len;
    Node *tail;

    Result(int len, Node *tail)
    {
        this->len = len;
        this->tail = tail;
    }
};

Result *getTailAndLen(Node *node)
{
    if (node == NULL)
        return NULL;

    int len = 1;
    Node *current = node;

    while (current->next != nullptr)
    {
        len += 1;
        current = current->next;
    }
    return new Result(len, current);
}

// Return pointer to a specific node in the list
Node* getKthNode(Node* longer, int len)
{
    Node* temp = longer;
    int i = 0;
    while(len>0 && i<len)
    {
        temp = temp->next;
        i++;
    }
    return temp;
}

// Return the Intersection Node pointer
Node *findIntersection(Node *h1, Node *h2)
{
    // If any of the 2 lists is empty, there is no intersection
    if (h1 == NULL || h2 == NULL)
        return NULL;

    // Get tail and lengths
    Result *r1 = getTailAndLen(h1);
    Result *r2 = getTailAndLen(h2);

    // If different tail nodes, then there's no intersection
    if (r1->tail != r2->tail)
        return NULL;

    Node *shorter = r1->len < r2->len ? h1 : h2;
    Node *longer = r1->len < r2->len ? h2 : h1;

    // Advance the longer linked list by the difference in lengths
    longer = getKthNode(longer, abs(r1->len-r2->len));

    // Move both pointers until collision occurs
    while(shorter!=longer)
    {
        shorter = shorter->next;
        longer = longer->next;
    }

    return longer;
}

int main()
{
    LinkedList *l1 = new LinkedList();
    LinkedList *l2 = new LinkedList();

    l1->insertNode(5);
    l1->insertNode(2);
    l1->insertNode(6);
    l1->insertNode(10);
    l1->insertNode(3); // 3 -> 10 -> 6 -> 2 -> 5

    l2->insertNode(6);
    l2->insertNode(7);
    l2->insertNode(11);
    l2->insertAfter(l1->getHead()->next->next->next); // 11 -> 7 -> 6 -> 6 -> 2 -> 5

    l1->printList(l1->getHead());
    l2->printList(l2->getHead());

    Node* intersect_node = findIntersection(l1->getHead(), l2->getHead());

    if(intersect_node!=NULL)
        cout<<"\nIntersection Node is: "<<intersect_node->data;
}