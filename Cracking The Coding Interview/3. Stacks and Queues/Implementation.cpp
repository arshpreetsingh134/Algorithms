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

// Queue Implementation
template <typename Q>
class Queue
{
    class Node
    {
    public:
        Q data;
        Node *next;

        Node(Q data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };

    Node *first;
    Node *last;

public:
    void Enqueue(Q item)
    {
        Node *new_node = new Node(item, nullptr);
        if (last != nullptr)
            last->next = new_node;
        last = new_node;

        if (first == nullptr)
            first = last;
    }

    Q Dequeue()
    {
        if (first == nullptr)
            return -1;

        Q item = first->data;
        first = first->next;

        if (first == nullptr)
            last = nullptr;

        return item;
    }

    Q peek()
    {
        if (first == nullptr)
            return -1;
        return first->data;
    }

    bool isEmpty()
    {
        return first == nullptr;
    }
};

int main()
{
    Stack<int> *myStack = new Stack<int>();

    myStack->push(8);
    myStack->push(10);
    myStack->push(6);
    myStack->push(15);

    cout << myStack->pop() << " ";
    cout << myStack->pop();

    Queue<int> *myQueue = new Queue<int>();

    myQueue->Enqueue(5);
    myQueue->Enqueue(8);
    myQueue->Enqueue(7);
    myQueue->Enqueue(10);

    cout << endl
         << myQueue->Dequeue() << " ";
    cout << myQueue->Dequeue();
}