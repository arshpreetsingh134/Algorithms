// Reverse a Singly LinkedList in θ(n) time and θ(1) (no-extra) space iteravtively.

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

    Node* getHead()
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

        // Store head node
        Node *temp = head;
        Node *prev = NULL;

        // If head node itself holds
        // the key to be deleted
        if (temp != NULL && temp->data == key)
        {
            head = temp->next; // Changed head
            delete temp;            // free old head
            return;
        }

        // Else Search for the key to be deleted,
        // keep track of the previous node as we
        // need to change 'prev->next' */
        while (temp != NULL && temp->data != key)
        {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL)
            return;

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        delete temp;
    }

    // This function prints contents of
    // linked list starting from the
    // given node
    void printList(Node* temp)
    {
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    // Method 1: Iterative
    Node* reverseList1()
    {
        // If LinkedList is empty or has just one node, 
        // it is trivially reversed
        if(head==NULL || head->next == NULL)
            return head;

        Node *list_to_do = head->next; // A pointer to the remaining list
        Node *reversed = head;         // A pointer to already reversed linked list

        reversed->next = NULL;

        while(list_to_do!=NULL)
        {
            Node* temp = list_to_do->next;

            list_to_do->next = reversed;
            reversed = list_to_do;
            list_to_do = temp;
        }

        return reversed;
    }

    // Method 2: Recursive
    Node* reverseList2(Node* node)
    {
        // empty list base case
        if (node == nullptr || node->next == nullptr)
            return node;

        Node* rev = reverseList2(node->next);     // recursively reverse the smaller {2, 3} case
                                // after: rest = {3, 2}

        node->next->next = node; // put the first item at the end of the list
        node->next = nullptr;     // (tricky step —— make a drawing)
        
        return rev;
    }
};

// Driver code
int main()
{

    // Start with the empty list
    LinkedList *obj = new LinkedList();

    // Add elements in linked list
    obj->insertNode(7);
    obj->insertNode(1);
    obj->insertNode(13);
    obj->insertNode(2);
    obj->insertNode(8);
    obj->insertNode(11);
    obj->insertNode(5);

    puts("Created Linked List: ");
    obj->printList(obj->getHead());

    Node *reversed = obj->reverseList2(obj->getHead());

    puts("\nLinked List after Reversing: ");
    obj->printList(reversed);

    return 0;
}
