// Sort the Stack (we can only use 2 stacks)

#include <iostream>
using namespace std;

// Stack Implementation
template <typename S>
class Stack
{
    class Node
    {
    public:
        S data;
        Node *next;

        Node(S data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };

    Node *top = nullptr;
    int size = 0;

public:
    S pop()
    {
        if (top == nullptr)
            return -1;

        S item = top->data;
        top = top->next;
        size--;
        return item;
    }

    void push(int data)
    {
        Node *new_node = new Node(data, top);
        top = new_node;
        size++;
    }

    S peek()
    {
        if (top == nullptr)
            return -1;
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    S returnSize()
    {
        return size;
    }
};

template <typename S>
class SortedStack
{
    // Declare the 2 stacks
    Stack<S> *ps;      // Primary Stack
        Stack<S> *ss; // Secondary Stack

public:
    SortedStack()
    {
        ps = new Stack<int>();
        ss = new Stack<int>();
    }

    void pushSorted(int value)
    {
        if (ps->isEmpty())
        {
            ps->push(value);
            return;
        }

        while (ps->peek() < value)
        {
            ss->push(ps->pop());
            if(ps->isEmpty())
                break;
        }

        ps->push(value);

        while (!ss->isEmpty())
        {
            ps->push(ss->pop());
        }
    }

    int popSorted()
    {
        return (ps->pop());
    }
};

int main()
{
    SortedStack<int> *s = new SortedStack<int>();

    s->pushSorted(8);
    s->pushSorted(10);
    s->pushSorted(5);
    s->pushSorted(50);

    cout << "\nValue " << s->popSorted() << " popped from the stack.";
    cout << "\nValue " << s->popSorted() << " popped from the stack.";
    cout << "\nValue " << s->popSorted() << " popped from the stack.";
    cout << "\nValue " << s->popSorted() << " popped from the stack.";
}
