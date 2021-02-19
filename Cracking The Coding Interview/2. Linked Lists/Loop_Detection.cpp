// Detect if the Linked List has a loop. If yes, return the node where it starts
// E.g.- INPUT: A -> B -> C -> D -> E -> C [the same C as earlier]
// OUTPUT: C

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
        int i = 0;
        while (temp != NULL && i<15)
        {
            cout << temp->data << " ";
            temp = temp->next;
            i++;
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

Node* findBeginning(Node* head)
{
    Node* slow = head;
    Node* fast = head;

    // First find the Collision Point, this will be (LOOP_SIZE-k) steps
    // into the LinkedList, where k is the 'non-looped' part of the list
    while(fast!=NULL || fast->next!=NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow==fast)  // Collision
            break;
    }

    // If there's no meeting point, i.e., fast reaches the end of list
    // so there should be no loop (based on the above while condition)
    if(fast==NULL || fast->next==NULL)
        return NULL;

    // Move 'slow' to head, keep 'fast' at meeting point. Each are k steps 
    // from the loop start. So if they move at the same pace, then they must
    // meet at the loop start
    slow = head;

    while(fast!=slow)
    {
        slow = slow->next;
        fast = fast->next;
    }

    // Both now point to the start of the loop, so we can return either of the 2
    return slow;
}


int main()
{
    LinkedList* l = new LinkedList();

    l->insertNode(11);
    l->insertNode(10);
    l->insertNode(9);
    l->insertNode(8);
    l->insertNode(7);
    l->insertNode(6);
    l->insertNode(5);
    l->insertNode(4);
    l->insertNode(3);
    l->insertNode(2);
    l->insertNode(1);

    l->insertAfter(l->getHead()->next->next->next);     // 1->2->3->4->5->6->7->8->9->10->11-
                                                        //          |<-__________________<-|

    l->printList(l->getHead());

    Node* loop_start = findBeginning(l->getHead());
    if(loop_start==NULL)
        cout<<"\nLoop not detected";
    else
        cout<<"\nLoop detected at "<<loop_start->data;
}
