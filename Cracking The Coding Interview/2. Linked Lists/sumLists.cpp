// You have two numbers represented by a Linked List in reverse order. Find their sum.
// E.g.- (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 +295 = 912
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

    // For Method 1: Function to reverse a LinkedList.
    // Returns a head ptr to the reversed LinkedList
    Node *reverseList()
    {
        // If Linked List is empty, or has just one element,
        // it is trivially reversed
        if (head == NULL || head->next == NULL)
            return head;

        Node *list_so_far = head->next;
        Node *reversed = head;
        reversed->next = NULL;

        while (list_so_far != NULL)
        {
            Node *temp = list_so_far->next;

            list_so_far->next = reversed;
            reversed = list_so_far;
            list_so_far = temp;
        }

        return reversed;
    }

    long returnNum()
    {
        Node *reversed = reverseList();
        long sum = 0;
        while (reversed->next != NULL)
        {
            sum += reversed->data;
            sum = sum * 10;
            reversed = reversed->next;
        }
        sum += reversed->data;
        return sum;
    }

    // For Method 2: Traverse the List recursively till it reaches
    // the end then calculate the number, coming backwards
    long recurseList(Node *node)
    {
        if (node == NULL)
            return 0;

        int sum = 0;
        sum = node->data + (recurseList(node->next) * 10);
        return sum;
    }
};

// Method 1: Reversing the list
int returnSum1(LinkedList *l1, LinkedList *l2)
{
    long num1 = l1->returnNum();
    long num2 = l2->returnNum();

    return num1 + num2;
}

// Method 2: Recursing through the list
int returnSum2(LinkedList *l1, LinkedList *l2)
{
    long num1 = l1->recurseList(l1->getHead());
    long num2 = l2->recurseList(l2->getHead());

    return num1 + num2;
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
    l1->printList(l1->getHead());
    l2->printList(l2->getHead());

    cout << "Sum of two numbers is: " << returnSum2(l1, l2);
    cout << "\nSum of two numbers is: " << returnSum1(l1, l2);
}