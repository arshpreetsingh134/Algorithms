// Given a LinkedList and an integer x, partition the LL in such a way that all < x elements occur before x and all >= x
// elements occur after x (O(n) time)
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
    // Print List
    void printList(Node *temp)
    {
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    // We store elements in 2 lists (before & after) and then merge them
    Node *Partition1(int x)
    {
        Node *node = head;
        Node *beforehead = nullptr; // Head of the LL before x
        Node *beforetail = nullptr; // Tail of the LL before x
        Node *afterhead = nullptr;  // Head of the LL after x
        Node *aftertail = nullptr;  // Tail of the LL after X

        while (node != nullptr)
        {
            Node *temp = node->next;
            node->next = nullptr;

            if (node->data < x)
            {
                // Check if before list is not already empty
                if (beforehead == nullptr)
                {
                    beforehead = node;
                    beforetail = beforehead;
                }
                else
                {
                    // Insert node into the end of before list
                    beforetail->next = node;
                    beforetail = beforetail->next;
                }
            }
            else
            {
                // Check if the after list is not already empty
                if (afterhead == nullptr)
                {
                    afterhead = node;
                    aftertail = afterhead;
                }
                else
                {
                    // Insert node into the end of after list
                    aftertail->next = node;
                    aftertail = aftertail->next;
                }
            }

            node = temp;
        }

        // If before list is empty
        if (beforehead == nullptr)
            return afterhead;

        // Merge 'before' and 'after' lists (automatically handles
        // the case when 'after' list is empty)
        beforetail->next = afterhead;
        return beforehead;
    }

    // Another method is to start a "new" list such that elements bigger
    // than x are put at the tail of the list and elements smaller are put
    // at the head
    Node *Partition2(int x)
    {
        Node *node = head;

        Node *start = node;
        Node *end = node;

        while (node != nullptr)
        {
            Node *next_node = node->next;
            if (node->data < x)
            {
                node->next = start;
                start = node;
            }
            else
            {
                end->next = node;
                end = node;
            }
            node = next_node;
        }
        end->next = nullptr;
        return start;
    }
};

int main()
{
    LinkedList *l = new LinkedList();
    int x = 4;

    l->insertNode(1);
    l->insertNode(2);
    l->insertNode(10);
    l->insertNode(5);
    l->insertNode(8);
    l->insertNode(5);
    l->insertNode(3);
    l->insertNode(6);

    cout << "Linked List is: ";
    l->printList(l->getHead());

    cout << "\nAfter partition, Linked List is: ";

    Node *part = l->Partition2(x);
    l->printList(part);
}