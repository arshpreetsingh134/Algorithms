// Implement a Stack with push(), pop() and getMinElement() operations in O(1) time.

#include <iostream>
#include <climits>
#include <exception>
using namespace std;

class Stack
{
    class myException : public exception
    {
    public:
        const char *what() const throw()
        {
            return "\nStack Underflow!\n";
        }
    };

    class Node
    {
    public:
        int data;
        int min;
        Node *next;

        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
            this->min = INT32_MAX;
        }
    };

    Node *head = nullptr;
    int size = 0;

public:
    void push(int value)
    {
        Node *new_node = new Node(value, head);

        if (size > 0)
        {
            if (value < new_node->next->min)
                new_node->min = value;
            else
                new_node->min = new_node->next->min;
        }
        else
            new_node->min = value;

        head = new_node;
        size++;
    }

    int pop()
    {
        try
        {
            if (size == 0)
                throw new exception();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        int item = head->data;

        head = head->next;
        size--;
        return item;
    }

    int getMin()
    {
        return head->min;
    }
};

int main()
{
    Stack *myStack = new Stack();

    myStack->push(2);
    myStack->push(1);
    myStack->push(8);
    myStack->push(10);
    myStack->push(6);
    myStack->push(15);
    myStack->push(1);
    myStack->push(0);

    cout << myStack->pop() << " popped\n";
    cout << myStack->pop() << " popped\n";

    cout << "\nMinimum element in the Stack: " << myStack->getMin();
    cout << endl;
}