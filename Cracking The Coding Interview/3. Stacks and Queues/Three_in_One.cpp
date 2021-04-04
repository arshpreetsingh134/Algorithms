// Implementing 3 stacks using 1 array- fixed (predetermined) size
#include <iostream>
#include <cmath>
#include <exception>
using namespace std;

class FixedMultiStack
{
    int numStacks = 3;
    int stackCapacity;
    int *stackSizes;
    int *stackValues;
    int arr_len;

    class myException: public exception
    {
    public:
        const char *what() const throw()
        {
            return "\nStack Underflow!\n";
        }
    };

public:
    FixedMultiStack(int stackCapacity)
    {
        this->stackCapacity = stackCapacity; // Capacity of each stack
                                             // (allocates an equal capacity to each stack)
        stackSizes = new int[numStacks]{};   // Stores the size of each stack
        arr_len = numStacks * stackCapacity; // Total length of the array
        stackValues = new int[arr_len];      // Array that stores the values of all stacks
    }

    // Return if stack is empty
    bool isEmpty(int stackNo)
    {
        return stackSizes[stackNo] == 0;
    }

    // Return if stack is full
    bool isFull(int stackNo)
    {
        return stackSizes[stackNo] == stackCapacity;
    }

    // Return the current offset value at a particular stack
    int offset(int stackNo)
    {
        return stackNo * stackCapacity;
    }

    // Return the top element's index of a stack
    int topOf(int stackNo)
    {
        return (offset(stackNo) + stackSizes[stackNo] - 1);
    }

    // Push value to the stack
    void push(int stackNo, int value)
    {
        // Check if we have space for the next element
        if(isFull(stackNo))
        {
            cout<<"\nStack overflow!\n";
            return;
        }
        
        stackSizes[stackNo]++;
        stackValues[topOf(stackNo)] = value;
        cout << value << " added at index " << stackSizes[stackNo] << " in stack " << stackNo + 1 << endl;
    }

    // Pop an element from the stack
    int pop(int stackNo)
    {
        int top;
        try
        {
            if (isEmpty(stackNo))
                throw new myException();

            top = stackValues[topOf(stackNo)];
            stackValues[topOf(stackNo)] = 0;
            stackSizes[stackNo]--;
        }
        catch (const std::exception *e)
        {
            e->what();
        }
        return top;
    }

    // Return the topmost element in the stack
    int peek(int stackNo)
    {
        try
        {
            if (isEmpty(stackNo))
                throw new myException();
        }
        catch (const std::exception *e)
        {
            e->what();
        }
        return stackValues[topOf(stackNo)];
    }

    // Prints the values in the Stack
    void printStack(int stackNo)
    {
        try
        {
            if (isEmpty(stackNo))
                throw new myException();

            for (int i = 0; i < stackSizes[stackNo]; i++)
                cout << stackValues[offset(stackNo) + i] << " ";
        }
        catch (const std::exception *e)
        {
            e->what();
        }
    }
};

int main()
{
    FixedMultiStack *obj = new FixedMultiStack(5);
    obj->push(1, 58);
    obj->push(2, 96);
    obj->push(2, 10);
    obj->push(0, 21);
    obj->push(0, 46);
    obj->push(0, 54);
    obj->push(0, 78);

    cout << "\nPopped: " << obj->pop(0);
    cout << "\nPopped: " << obj->pop(2);
    cout << "\nPopped: " << obj->pop(2);
    obj->pop(2); // This will generate exception

    int stackNo = 0;
    cout << "\nTopmost element in stack " << stackNo + 1 << ": " << obj->peek(stackNo);
    cout << "\nValues in stack " << stackNo + 1 << " are: ";
    obj->printStack(stackNo);
}