// Check if a Linked List is a palindrome
#include <iostream>
#include <stack>
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

Node *reverseList(Node* node)
{
    Node* head = nullptr;
    while(node!=nullptr)
    {
        Node* n = new Node(node->data, nullptr);
        n->next = head;
        head = n;
        node = node->next;
    }
    return head;
}

bool isEqual(Node* a, Node* b)
{
    while(a!=nullptr && b!=nullptr)
    {
        if(a->data!=b->data)
            return false;
        a = a->next;
        b = b->next;
    }
    return (a==nullptr && b==nullptr);

}

// Method 1: Reverse & Compare
bool isPalindrome1(Node* node)
{
    Node* head = node;
    Node* reversed = reverseList(node);
    return isEqual(head, reversed);
}

// Method 2: Using a Stack Data Structure (iteratively)
bool isPalindrome2(Node* node)
{
    Node* slow = node;
    Node* fast = node;

    stack<int> first_half;

    // Push elements from the first-half of the LL into the stack
    // When the fast runner ptr (which is moving at 2x speed) reaches
    // the end of LL, the slow runner reaches the middle
    while(fast!=NULL && fast->next!=NULL)
    {
        first_half.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }

    // Has odd no. of elements, so skip the middle
    if(fast!=NULL)
        slow = slow->next;

    while(slow!=NULL)
    {
        // Check if the values are different
        if(slow->data!=first_half.top())
            return false;

        first_half.pop();
        slow = slow->next;
    }
    return true;
}

// Method 3: Recursive Approach

// Wrapper Class
class Result
{
    public:
    bool result;
    Node* node;

    Result(){}

    Result(bool result, Node* node)
    {
        this->result = result;
        this->node = node;
    }
};

// In this recursive function, each call compares its head to "returned_node" from
// the next recursive call in the call stack, and then passes returned_node->next
// down the stack. In this way, every i-th node is compared to node n-i. If at any 
// point, values donot match, we return false.
Result* isPalindromeRecurse(Node* head, int length)
{
    // Base Case: When control reaches the top of recursive stack (i.e., middle of list)
    if(head==NULL || length<=0)     // Even no. of nodes
        return new Result(true, head);
    else if(length == 1)                           // Odd no. of nodes
        return new Result(true, head->next);

    // Recurse on the sublist
    Result* r = isPalindromeRecurse(head->next, length-2);

    // In case if sublists are not a palindrome, return false
    if(!r->result || r->node==NULL)
        return r;

    // Check if the returned_node matches the corresponding node
    r->result = (r->node->data == head->data);

    r->node = r->node->next;

    return r;
}

bool isPalindrome3(LinkedList* l)
{
    int list_len = l->ll_length();
    Result *r = isPalindromeRecurse(l->getHead(), list_len);
    return r->result;
}

int main()
{
    LinkedList *l = new LinkedList();
    l->insertNode(1);
    l->insertNode(2);
    l->insertNode(3);
    l->insertNode(5);
    l->insertNode(3);
    l->insertNode(2);
    l->insertNode(1);

    cout << "Is a Palindrome? " << isPalindrome1(l->getHead());
    cout << "\nIs a Palindrome? " << isPalindrome2(l->getHead());
    cout << "\nIs a Palindrome? " << isPalindrome3(l);
}