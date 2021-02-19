// Return k-th to last element in a Singly Linked List
#include <iostream>
using namespace std;

// A linked list node
class Node
{
public:
    int data;
    Node *next;
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

    // Deletes the first occurrence of key in the
    // linked list
    void deleteNode(int key)
    {
        Node *temp = head;
        Node *prev = NULL;

        if (temp != NULL && temp->data == key)
        {
            head = temp->next; 
            delete temp;       
            return;
        }

        while (temp != NULL && temp->data != key)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;

        prev->next = temp->next;

        delete temp;
    }

    void printList(Node *temp)
    {
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

// Method 1: Simple Traversal (O(n) time)
    int findFromLast1(int k)
    {
        Node* temp = head;
        int count = 0;

        while(temp)
        {
            count++;
            temp = temp->next;
        }

        temp = head;
        int end = count-k;
        int i = 0;

        while(i<end)
        {
            temp = temp->next;
            i++;
        }
        return temp->data;
    }

// Method 2: Recursing through the Linked list till the end counter is set 
// to 0, and then is incremented at each back recursion (O(n) space)
    int findFromLast2(Node *head, int k)
    {
        // Base Case- When we reach the end of Linked List
        // return a counter set to 0
        if(head==nullptr)
            return 0;

        int index = findFromLast2(head->next, k)+1;

        // If recursion reaches at index k, print data and exit
        // the recursion by setting head = null (Base Case)
        if(index==k)
        {
            cout<<"\n"<<k<<"-th element from the last: "<<head->data;
            head = nullptr;
        }

        return index;
    }

// Same approach, but using pointers
    Node* findFromLastRec(Node *head, int &index, int k)
    {
        // Base Case- When we reach the end of Linked List
        // return a counter set to 0
        if (head == nullptr)
            return nullptr;

        // Keep returning a nullptr until k-th from last element
        Node* rec_node = findFromLastRec(head->next, index, k);
        index = index+1;

        // If recursion reaches at index k, print data and exit
        // the recursion by setting head = null (Base Case)
        if (index == k)
            return head;

        return rec_node;
    }

    int findFromLast2(int k)
    {
        int i = 0;
        Node *n = findFromLastRec(head, i, k);
        return n->data;
    }

// Method 3: Iterative: Take 2 pointers, k positions apart, when 2nd
// pointer reaches the end of Linked List, 1st reaches at (length-k)
    int findFromLast3(int k)
    {
        Node* n1 = head;
        Node* n2 = head;

        int i = 0;
        while(i<k)
        {
            n2 = n2->next;
            i++;
        }

        while(n1)
        {
            if(n2==nullptr)
                break;
            n1 = n1->next;
            n2 = n2->next;
        }

        return n1->data;

    }
};

int main()
{
    LinkedList *l = new LinkedList();
    int k = 3;
    l->insertNode(5);
    l->insertNode(6);
    l->insertNode(8);
    l->insertNode(2);
    l->insertNode(18);
    l->insertNode(10);
    l->insertNode(3);
    l->insertNode(7);

    cout<<"Linked List is: ";
    l->printList(l->getHead());

    cout<<endl<<k<<"-th element from the last: "<<l->findFromLast1(k);

    l->findFromLast2(l->getHead(), k);

    cout << endl << k << "-th element from the last: " << l->findFromLast2(k);

    cout << endl << k << "-th element from the last: " << l->findFromLast3(k);
}