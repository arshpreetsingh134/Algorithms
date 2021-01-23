#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    Node *next;

    Node(int x) : val(x), next(NULL){};

    // For deleting a dynamically allocated user-defined memory pointed by a pointer
    // static void operator delete(void* ptr, std::size_t sz)
    // {
    //     //cout << "custom delete for size " << sz <<endl;
    //     delete (ptr); // ::operator delete(ptr) can also be used
    // }
};

class MyLinkedList
{
    Node *head;

public:
    /** Initializing the Linked List */
    MyLinkedList()
    {
        head = NULL;
    }

    //Node* head = new Node();

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index)
    {
        Node *curr_node = head;
        int i = 0;
        while (i != index)
        {
            if (curr_node == NULL)
                return -1;

            curr_node = curr_node->next;
            i++;
        }

        return curr_node->val;
    }

    /** Add a node of value val before the first element of the linked list. After the 
     * insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val)
    {
        Node *curr_node = new Node(val);
        curr_node->next = head;
        head = curr_node;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val)
    {
        Node *curr_node = head;

        Node *new_node = new Node(val);
        // new_node->val = val;
        // new_node->next = NULL;

        while (curr_node->next != NULL)
        {
            curr_node = curr_node->next;
        }

        curr_node->next = new_node;
    }

    /** Add a node of value val before the index-th node in the linked list. If index 
     * equals to the length of linked list, the node will be appended to the end of 
     * linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val)
    {
        //19 12 8 10 7 22
        // (After adding 22 at index 2) -> 19 12 22 8 10 7 22

        Node *curr_node = head;
        Node *prev_node;
        Node *new_node = new Node(val);

        int i = 0;
        while (i != index)
        {
            if (curr_node == NULL)
                return;
            prev_node = curr_node;
            curr_node = curr_node->next;
            i++;
        }

        prev_node->next = new_node;
        new_node->next = curr_node;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index)
    {
        Node *curr_node = head;
        Node *prev_node = NULL;

        int i = 0;
        while (i != index)
        {
            if (curr_node == NULL)
                return;
            prev_node = curr_node;
            curr_node = curr_node->next;
            i++;
        }

        if(prev_node)
            prev_node->next = curr_node->next;
        
        curr_node = NULL;
        delete curr_node;
        
        if(curr_node==NULL)
            cout<<"\n\nDeleted\n";
    }

    void display()
    {
        Node *curr_node = head;
        cout << endl;
        while (curr_node->next != NULL)
        {
            cout << curr_node->val << " ";
            curr_node = curr_node->next;
        }
        cout << curr_node->val;
    }
};

int main()
{
    MyLinkedList *obj = new MyLinkedList();

    int param_1 = obj->get(1);
    cout << "\nFetched value is: " << param_1 << endl;

    obj->addAtHead(8);
    obj->addAtHead(12);
    obj->addAtHead(19);
    obj->addAtTail(10);
    obj->addAtTail(7);
    obj->addAtTail(22);

    obj->display();

    obj->addAtIndex(3, 48);

    obj->display();

    obj->deleteAtIndex(3);

    obj->display();

    cout << endl;
}