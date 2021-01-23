#include <iostream>
using namespace std;

class MyLinkedList
{
    struct Node
    {
    public:
        int val;
        Node *next;

        /** Initializing the Linked List **/
        Node(int val = 0, Node *next = nullptr)
        {
            this->val = val;
            this->next = next;
        }
    };

    Node *head, *tail;

public:
    MyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index)
    {
        Node *curr_node = head;
        int i = 0;
        while (i != index)
        {
            if (curr_node)
                curr_node = curr_node->next;
            else
                break;
            i++;
        }

        if (curr_node)
            return curr_node->val;

        return -1;
    }

    /** Add a node of value val before the first element of the linked list. After the 
     * insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val)
    {
        head = new Node(val, head);

        // If tail is NULL
        if (!tail)
            tail = head;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val)
    {
        if (!tail)
            tail = new Node(val);
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }

        // If head is NULL
        if (!head)
            head = tail;
    }

    /** Add a node of value val before the index-th node in the linked list. If index 
     * equals to the length of linked list, the node will be appended to the end of 
     * linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val)
    {
        // 19 12 8 10 7 22
        // (After adding 22 at index 2) -> 19 12 22 8 10 7 22

        Node *curr_node = head, *pre_node = nullptr;

        int i = 0;
        while (i != index)
        {
            if (!curr_node)
                break;
            pre_node = curr_node;
            curr_node = curr_node->next;
            i++;
        }

        Node *new_node = new Node(val, curr_node);

        if (index == 0)
        {
            curr_node = new_node;
            head = curr_node;
            return;
        }

        if (!pre_node)
            head = new_node;

        if (!curr_node)
            tail = new_node;

        if (pre_node)
            pre_node->next = new_node;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index)
    {
        Node *curr_node = head, *pre_node = nullptr;

        int i = 0;
        while (i != index)
        {
            if (!curr_node)
                break;
            pre_node = curr_node;
            curr_node = curr_node->next;
            i++;
        }

        if (!curr_node)
            return;
        if (pre_node)
            pre_node->next = curr_node->next;
        else
            head = curr_node->next;

        if (!curr_node->next)
            tail = pre_node;

        delete curr_node;
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

    obj->addAtHead(2);
    obj->deleteAtIndex(1);
    obj->addAtHead(2);
    obj->addAtHead(7);
    obj->addAtHead(3);
    obj->addAtHead(2);
    obj->addAtHead(5);
    obj->addAtTail(5);
    cout<<endl<<"At index 6: "<<obj->get(6)<<endl;
    
    
    // obj->deleteAtIndex(6);
    // obj->deleteAtIndex(4);

    cout << endl;

    obj->display();

}