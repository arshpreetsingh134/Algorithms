// Circular linked list is a linked list where all nodes are connected to form a circle. There is no NULL at the end.

// Singly Circular LinkedList
#include <iostream>
using namespace std;

struct Node
{
public:
    int val;
    Node *next;
    Node(int val = 0, Node *next = nullptr)
    {
        this->val = val;
        this->next = next;
    }
};

Node *head = nullptr;
Node *tail = nullptr;

// Add the Node to an empty CLL
void addToEmpty(int value)
{
    if (tail)
        return;

    Node *new_node = new Node(value);
    // For the first node (make it circular)
    new_node->next = new_node;
    tail = new_node;
    head = new_node;
}

// Add a node at the beginning of a CLL
void addFront(int value)
{
    if (!head)
    {
        addToEmpty(value);
        return;
    }

    Node *new_node = new Node(value, head);
    Node *temp = head;

    // If the LinkedList is not NULL,
    // set the next of last node

    // while(temp->next!=head)
    //     temp = temp->next;
    // temp->next = new_node;

    tail->next = new_node;

    head = new_node;
}

// Add a node at the end of CLL
void addLast(int value)
{
    if (!tail)
    {
        addToEmpty(value);
        return;
    }

    Node *new_node = new Node(value, head);
    tail->next = new_node;
    tail = new_node;
}

// Add a node after the node containing the given item
void addAfter(int value, int item)
{
    if (!tail)
    {
        addToEmpty(value);
        return;
    }

    Node* new_node;
    Node* temp;

    temp = tail->next;

    do
    {
        if(temp->val == item)
        {
            new_node = new Node(value, temp->next);
            temp->next = new_node;

            if(temp==tail)
                tail = new_node;
            return;
        }

        temp = temp->next;

    }while(temp->next!=tail->next);

}

// Print the LinkedList
void printList()
{
    Node *temp = head;
    if (head != NULL)
    {
        do
        {
            cout << temp->val << " ";
            temp = temp->next;
        } while (temp != head);
    }
}

int main()
{
    Node *head = NULL;

    addFront(12);
    addFront(56);
    addFront(2);
    addFront(11);

    addLast(88);

    addAfter(14, 56);

    cout << "Contents of Circular Linked List:\n ";
    printList();
}