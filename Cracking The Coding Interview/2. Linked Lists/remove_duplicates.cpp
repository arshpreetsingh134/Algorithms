// Remove duplicates from an unsorted Singly Linked List
#include <iostream>
#include <unordered_map>
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

// Method 1: Using Hash Table (O(n))
    void removeDuplicates1()
    {
        unordered_map<int,int> dup;

        Node* temp = head;

        while(temp)
        {
            dup[temp->data]++;

            if(dup[temp->data]>1)
                deleteNode(temp->data);
                
            temp = temp->next;
        }
    }

// Method 2: Same approach, different code (O(n))
    void removeDuplicates2()
    {
        unordered_map<int,int> dup2;
        Node *temp = head;
        Node *prev = nullptr;

        while(temp!=NULL)
        {
            if(dup2[temp->data]==1)
                prev->next = temp->next;
            else
            {
                dup2[temp->data]=1;
                prev = temp;
            }

            temp = temp->next;
        }
    }

// Method 3: Without using buffer (O(1) space, O(n^2) time)
    void removeDuplicates3()
    {
        Node* temp = head;
        while(temp!=nullptr)
        {
            Node* runner = temp;
            while(runner->next!=nullptr)
            {
                if(temp->data == runner->next->data)
                {
                    //temp->next = runner->next->next;
                    runner->next = runner->next->next;
                }
                else
                    runner = runner->next;
            }
            temp = temp->next;
        }
    }
};

int main()
{
    LinkedList *l = new LinkedList();

    l->insertNode(5);
    l->insertNode(6);
    l->insertNode(6);
    l->insertNode(2);
    l->insertNode(8);
    l->insertNode(10);
    l->insertNode(2);
    l->insertNode(5);

    cout<<"Linked List before deletion of duplicates :- ";
    l->printList(l->getHead());

    l->removeDuplicates3();
    cout<<"\nLinked List after deletion of duplicates :- ";
    l->printList(l->getHead());
}