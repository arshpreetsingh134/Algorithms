// Linked List Implementation with extra functionality (addAtHead, addAtTail, addAtIndex,
// deleteAtHead, deleteAtTail, deleteAtIndex)

#include <iostream>
using namespace std;

struct Node
{
public:
    int val;
    Node *next;
    Node(int x) : val(x), next(NULL){};
};

class MyLinkedList
{
    Node *head;
    Node *tail;
    int length;

public:
    MyLinkedList()
    {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    int get(int index)
    {
        if (index >= length)
            return -1;

        Node *curr_node = head;
        int i = 0;
        while (i != index)
        {
            curr_node = curr_node->next;
            i++;
        }
        return curr_node->val;
    }

    void addAtHead(int val)
    {
        Node *new_node = new Node(val);
        new_node->next = head;
        head = new_node;
        length++;

        if (length == 1)
            tail = head;
    }

    void addAtTail(int val)
    {
        Node *new_node = new Node(val);

        if (tail != NULL)
            tail->next = new_node;
        
        tail = new_node;
        length++;
        if (length == 1)
            head = tail;
    }

    void addAtIndex(int index, int val)
    {
        //19 12 8 10 7 22
        // (After adding 22 at index 2) -> 19 12 22 8 10 7 22

        Node *curr_node = head;

        if (index > length)
        {
            return;
        }

        if (index == length)
        {
            addAtTail(val);
            return;
        }

        if (index == 0)
        {
            addAtHead(val);
            return;
        }

        Node *new_node = new Node(val);

        int i = 0;
        while (i != index - 1)
        {
            curr_node = curr_node->next;
            i++;
        }

        new_node->next = curr_node->next;
        curr_node->next = new_node;
        length++;
    }

    void deleteAtHead()
    {
        if(length==0)
            return;

        if (length == 1)
        {
            // 19 -> delete 19
            delete head;
            head = NULL;
            length--;
            return;
        }

        // 12 22 78 52 32
        Node *temp = head;
        head = temp->next;
        length--;
        delete temp;
    }

    void deleteAtTail()
    {
        Node *curr_node = head;
        int i = 0;
        while (i != length - 2)
        {
            curr_node = curr_node->next;
            i++;
        }
        curr_node->next = NULL;
        delete tail;
        tail = curr_node;
        length--;
    }

    void deleteAtIndex(int index)
    {
        //19 12 8 10 7 22
        // (After deleting 10 from index 3) -> 19 12 8 7 22

        // 19 28

        if (length == 0)
            return;

        if (index >= length)
        {
            cout << "\nNothing to delete here.";
            return;
        }

        if (index == 0)
        {
            deleteAtHead();
            return;
        }

        if (index == length - 1)
        {
            deleteAtTail();
            return;
        }

        Node *curr_node = head;
        Node *temp;

        int i = 0;

        while (i != index - 1)
        {
            curr_node = curr_node->next;
            i++;
        }

        if (curr_node != NULL)
        {
            temp = curr_node->next;
            if (temp != NULL)
                curr_node->next = temp->next;
            delete temp;
        }

        length--;
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
    
    obj->addAtTail(87);
    obj->addAtHead(8);
    obj->addAtHead(12);
    obj->deleteAtHead();
    obj->addAtHead(19);
    obj->addAtTail(10);
    obj->addAtTail(7);
    obj->addAtTail(22);

    cout<<endl<<obj->get(1);

    obj->display();

    obj->addAtIndex(2, 48);

    obj->display();

    obj->deleteAtIndex(5);

    obj->display();

    cout << endl;
}