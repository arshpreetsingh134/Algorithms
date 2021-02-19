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

    S push(int data)
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
class Queue
{
    // Declare the 2 stacks
    Stack<S> *s1;          // Stack having the newest elements on top
    Stack<S> *s2;          // Stack having the oldest elements on top

    // Move all elements from s1 (stack with newest elements on top) to s2 (stack
    // with oldest elements on top), in order to perform pop() operations on s2
    void shiftStacks()
    {
        if(s2->isEmpty())
        {
            while(!s1->isEmpty())
            {
                s2->push(s1->pop());
            }
        }
    }

public:
    Queue()
    {
        s1 = new Stack<S>();
        s2 = new Stack<S>();
    }

    int size()
    {
        return s1->returnSize() + s2->returnSize();
    }

    void add(S val)
    {
        // Push to s1, which always have the newest elements on the top
        s1->push(val);
    }

    S remove()
    {
        shiftStacks();      // To ensure that s2 contains all elements currently added
        return s2->pop();     // Pop the oldest item from stack s2
    }

    S peek()
    {
        shiftStacks();
        return s2->peek();
    }

};

int main()
{
    Queue<int> *obj = new Queue<int>();

    obj->add(8);
    obj->add(10);
    obj->add(6);

    cout << endl
         << obj->remove();
    cout << " \n"
         << obj->remove();
    cout << " \n"
         << obj->remove();

    obj->add(12);
    obj->add(5);
    obj->add(2);

    cout << endl
         << obj->remove();
    cout << " \n"
         << obj->remove();
    cout << " \n"
         << obj->remove();
}