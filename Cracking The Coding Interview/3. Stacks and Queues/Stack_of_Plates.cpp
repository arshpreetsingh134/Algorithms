// Implementing a real-world stack of plates such that a new stack is automatically
// created once the current stack reaches its maximum threshold.

#include <iostream>
#include <vector>
using namespace std;

class Stack
{
    class Node
    {
    public:
        int data;
        Node *next;

        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };

    Node *top = nullptr;
    Node *bottom;
    int size = 0;

public:
    int pop()
    {
        if (top == nullptr)
            return -1;

        int item = top->data;
        top = top->next;
        size--;
        return item;
    }

    void push(int data)
    {
        Node *new_node = new Node(data, top);
        top = new_node;
        size++;
        if (size == 1)
            bottom = top;
    }

    int peek()
    {
        if (top == nullptr)
            return -1;
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    int returnSize()
    {
        return size;
    }

    int removeBottom()
    {
        int curr = bottom->data;
        bottom = bottom->next;
        size--;
        return curr;
    }
};

class SetOfStacks : public Stack
{
    int threshold; // Capacity of each stack
    vector<Stack> stackArr;
    int currIndex;

    int leftShift(int index, bool removeTop)
    {
        int removed_item;

        if (removeTop)
            removed_item = stackArr[index].pop();
        else
            removed_item = stackArr[index].removeBottom();

        if (stackArr[index].isEmpty())
            stackArr.erase(stackArr.end() - 1);
        else if (stackArr.size() > index + 1)
        {
            int v = leftShift(index + 1, false);
            stackArr[index].push(v);
        }
        return removed_item;
    }

public:
    SetOfStacks(int threshold)
    {
        this->threshold = threshold;
        stackArr.push_back(*(new Stack()));
        this->currIndex = 0;
    }

    void push(int value)
    {
        if (stackArr[currIndex].returnSize() == threshold)
        {
            stackArr.push_back(*(new Stack()));
            currIndex++;
            stackArr[currIndex].push(value);
        }
        else
            stackArr[currIndex].push(value);
    }

    int pop()
    {
        int del = stackArr[currIndex].pop();
        if (stackArr[currIndex].isEmpty())
        {
            //stackArr.erase(stackArr.end() - 1);
            currIndex--;
        }
        return del;
    }

    int peek()
    {
        return stackArr[currIndex].peek();
    }

    // Pop operation on a specific subStack (roll over all the subsequent stack
    // elements by one position)
    int popAt(int index)
    {
        return (leftShift(index, true));
    }
};

int main()
{
    SetOfStacks *s = new SetOfStacks(3);

    s->push(10);
    s->push(30);
    s->push(50);
    s->push(70);
    s->push(90);
    s->push(100);
    s->push(48);
    s->push(59);
    s->push(62);
    s->push(27);

    cout << "\nValue " << s->pop() << " popped from stack";
    cout << "\nValue " << s->pop() << " popped from stack";
    cout << "\nValue " << s->pop() << " popped from stack";
    cout << "\nValue " << s->pop() << " popped from stack" << endl;

    cout << "Peek Element: " << s->peek() << endl;

    cout << "\nPop at: " << s->popAt(1) << endl;
}
