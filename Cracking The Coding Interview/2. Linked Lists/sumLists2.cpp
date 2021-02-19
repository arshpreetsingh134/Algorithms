#include <iostream>
using namespace std;

// A linked list node
class Node
{
public:
    int data;
    Node *next;

    Node(){}

    Node(int data, Node* next)
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
};

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

Node *returnSumNode(Node *l1, Node *l2, int carry)
{
    if (l1 == NULL && l2 == NULL && carry == 0)
        return NULL;

    int value = carry;
    

    if (l1 != NULL)
        value += l1->data;
    
    if (l2 != NULL)
        value += l2->data;

    Node *result = new Node(value % 10, nullptr); // Value at ones place is stored in 'result'

    // Recurse on the subsequent nodes
    if (l1 != NULL || l2 != NULL)
    {
        Node *next_node = returnSumNode(l1 == NULL ? NULL : l1->next, l2 == NULL ? NULL : l2->next, value >= 10 ? 1 : 0);
        result->next = next_node;
    }

    return result;
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

    Node *result = returnSumNode(l1->getHead(), l2->getHead(), 0);
    cout << "Sum of two numbers is: ";
    printList(result);
}