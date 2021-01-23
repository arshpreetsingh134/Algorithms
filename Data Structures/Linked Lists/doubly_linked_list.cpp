// A Doubly Linked List can be traversed in both forward and backward direction.
// So a node of a DLL contains two pointers- next and prev

#include <iostream>
using namespace std;

class MyLinkedList
{
public:
    struct Node
    {
    public:
        int val;
        Node *next; // Pointer to next node in DLL
        Node *prev; // Pointer to previous node in DLL

        // Initializing the Linked List
        Node(int val = 0, Node *prev = nullptr, Node *next = nullptr)
        {
            this->val = val;
            this->prev = prev;
            this->next = next;
        }
    };

    Node *head, *tail;

    MyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    /** Get the index-th node in the linked list. If the index is invalid, return NULL. */
    Node* get(int index)
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
            return curr_node;

        return nullptr;
    }

    // Add a Node at the head of a DLL
    Node* addFront(int value)
    {
        Node *new_node = new Node(value, nullptr, head);
        if (head)
            head->prev = new_node;
        head = new_node;

        // If tail is NULL
        if(!tail)
            tail = head;

        return head;
    }

    // Add a Node after a given Node
    Node* addAfter(struct Node* prev_node, int value)
    {
        Node *new_node = new Node(value, prev_node, prev_node->next);
        Node *next_node = prev_node->next;

        if(next_node)
            next_node->prev = new_node;

        prev_node->next = new_node;

        if(!new_node->next)
            tail = new_node;

        return tail;
    }

    // Add a Node before a given Node
    Node* addBefore(struct Node* next_node, int value)
    {
        Node *new_node = new Node(value, next_node->prev, next_node);
        Node *prev_node = next_node->prev;
        
        if(prev_node)
            prev_node->next = new_node;

        next_node->prev = new_node;

        // If new_node is added at the first position, point head to it
        if(!(new_node->prev))
            head = new_node;

        return new_node;
    }

    // Add a node at the end of a DLL
    Node* addLast(int value)
    {
        Node* new_node = new Node(value, tail, nullptr);
        Node* prev_node = tail;

        if(prev_node)
            prev_node->next = new_node;

        if(!new_node->prev)
            head = new_node;

        tail = new_node;
    }

    void deleteNode(Node* del_node)
    {
        // In case if the node doesn't exist
        if(!del_node)
            return;

        // If node to be deleted is the head node
        if(!del_node->prev)
            head = del_node->next;
        else
            del_node->prev->next = del_node->next;

        // Check if the node to be deleted is not the last node
        if(del_node->next)
            del_node->next->prev = del_node->prev;
        else
            tail = del_node->prev;
        
        free(del_node);
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
    MyLinkedList *dll = new MyLinkedList();
    MyLinkedList::Node* head = dll->addFront(9);
  
    MyLinkedList::Node* tail = dll->addAfter(head, 15);

    dll->addBefore(tail, 56);

    dll->addAfter(head, 20);

    dll->addLast(48);

    dll->display();

    MyLinkedList::Node *node = dll->get(0);

    dll->deleteNode(node);

    dll->display();
}

