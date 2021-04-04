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

void sortStack(Stack<int> &s)
{
    Stack<int> r;
    while (!s.isEmpty())
    {
        int temp = s.pop();

        while (!r.isEmpty() && temp < r.peek())
        {
            s.push(r.pop());
        }
        r.push(temp);
    }

    while (!r.isEmpty())
    {
        s.push(r.pop());
    }
}

int main()
{
    Stack<int> *s = new Stack<int>();

    s->push(2);
    s->push(1);
    s->push(0);
    s->push(6);
    s->push(1);
    s->push(4);

    sortStack(*s);

    cout << "Topmost Element: " << s->peek();

    cout << "\nValue " << s->pop() << " popped from the stack.";
    cout << "\nValue " << s->pop() << " popped from the stack.";
    cout << "\nValue " << s->pop() << " popped from the stack.";
    cout << "\nValue " << s->pop() << " popped from the stack.";
    cout << "\nValue " << s->pop() << " popped from the stack.";
    cout << "\nValue " << s->pop() << " popped from the stack." << endl;
}