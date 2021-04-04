// Implementing 3 stacks using 1 array- fixed (predetermined) size
#include <iostream>
#include <vector>
#include <exception>
using namespace std;
int N; // Size of the Main Array- Declared Globally

class Stacks
{
private:
    // Sub-class for handling exceptions
    class myException : public exception
    {
    public:
        const char *what() const throw()
        {
            return "\nStack Underflow!\n";
        }
    };

    // Sub-class for holding a set of data about each stack
    class stackInfo
    {
    public:
        int startIndex, stackSize, capacity;

        stackInfo(){};

        stackInfo(int startIndex, int capacity)
        {
            this->startIndex = startIndex; // Index of start of each stack
            this->capacity = capacity;     // Capacity of each stack
            this->stackSize = 0;
        }

        // Adjusting the index accordingly (wrapping around)
        // if it exceeds or preceeds the array constraints
        int adjustIndex1(int index)
        {
            int max = N; // N;
            return (((index % max) + max) % max);
        }

        // Index of topmost element of the Stack
        int lastElementIndex()
        {
            return (adjustIndex1(startIndex + stackSize - 1));
        }

        // Index of topmost position in the Stack
        int lastCapacityIndex()
        {
            return (adjustIndex1(startIndex + capacity - 1));
        }

        // Check if an index on the full array is within the stack boundaries.
        // The stack can wrap around to the start of the array
        bool isWithinStackCapacity(int index)
        {
            // If outside of bounds of array, return false
            if (index < 0 || index >= N)
                return false;

            // If inside the bounds of array but wraps around,
            // then first adjust it, and then check
            int newIndex = index < startIndex ? index + N : index;
            int end = startIndex + capacity;
            return (startIndex < newIndex && newIndex < end);
        }

        // Check if the stack is empty
        bool isEmpty()
        {
            return (stackSize == 0);
        }

        // Check if the stack is full
        bool isFull()
        {
            return (stackSize == capacity);
        }
    };

    stackInfo *StackInfo;                   // Array of 3 stacks (info)
    vector<int> mainArr{vector<int>(N, 0)}; // Array of values (the main array to hold 3 stacks)
    int numStacks;
    int defaultSize;

    // Function Prototypes
    int totalElementsInArray(); // Returns the no. of items actually present in the array
    bool allStacksAreFull();    // Check if all stacks are full
    void shift(int);            // Shifting stacks one by one to make more space
    void expand(int);           // Expand stack by shifting over other stacks
    int adjustIndex(int);       // Adjust the given index so as to be within the range
    int previousIndex(int);     // Fetch the previous index in the array
    int nextIndex(int);         // Fetch the next index in the array

public:
    // Constructor for creating metadata for all the stacks.
    // We pass the no. of stacks we need (3) and the default
    // size of each stack as parameters
    Stacks(int numStacks, int defaultSize)
    {
        StackInfo = new stackInfo[numStacks];

        this->numStacks = numStacks;
        this->defaultSize = defaultSize;

        for (int i = 0; i < numStacks; i++)
        {
            StackInfo[i] = stackInfo(defaultSize * i, defaultSize);
        }

        //mainArr.resize(numStacks * defaultSize);
    }

    // Push value onto stackNo, shifting/ expanding stacks as necessary
    void push(int stackNo, int value)
    {
        if (allStacksAreFull())
        {
            cout << "Stack Overflow";
            return;
        }

        // If stack is full, expand it
        if (StackInfo[stackNo].isFull())
            expand(stackNo);

        // Find the index of the top element in the array + 1, and increment the
        // stack pointer
        StackInfo[stackNo].stackSize++;
        mainArr[StackInfo[stackNo].lastElementIndex()] = value;
    }

    // Remove value from the stack
    int pop(int stackNo)
    {
        int del;
        try
        {
            if (StackInfo[stackNo].isEmpty())
                throw new exception();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        // Remove last element from the stack
        int curr_index = StackInfo[stackNo].lastElementIndex();
        del = mainArr[curr_index];
        mainArr[curr_index] = 0;
        StackInfo[stackNo].stackSize--;
        return del;
    }

    // Fetch the top element of stack
    int peek(int stackNo)
    {
        try
        {
            if (StackInfo[stackNo].isEmpty())
                throw new exception();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return mainArr[StackInfo[stackNo].lastElementIndex()];
    }

    void displayStacks()
    {
        cout << endl;
        for (int i = 0; i < numStacks; i++)
        {
            stackInfo si = StackInfo[i];
            cout << "\nStack No." << i + 1 << ": ";

            for (int j = si.startIndex; j <= si.lastElementIndex(); j++)
            {
                if (j > N)
                    j = adjustIndex(j);

                cout << mainArr[j] << " ";
            }
            cout << endl;
        }
    }
};

int Stacks::totalElementsInArray()
{
    int size_arr = 0;

    for (int i = 0; i < numStacks; i++)
        size_arr += StackInfo[i].stackSize;
    return size_arr;
}

bool Stacks::allStacksAreFull()
{
    return (N == totalElementsInArray());
}

// Shift items in stack over by one element. If we have available capacity,
// then we'll end up shrinking the stack by one element. If we don't have
// available capacity, then we'll need to shift the next stack over too.
void Stacks::shift(int stackNo)
{
    cout << "\nShifting Stack No." << stackNo;

    // If the current stack is full, keep shifting the
    // elements recursively until there is a space available
    if (StackInfo[stackNo].stackSize >= StackInfo[stackNo].capacity)
    {
        int nextStackNo = (stackNo + 1) % numStacks;
        shift(nextStackNo);
        StackInfo[stackNo].capacity++;
    }

    // Shift all elements of the current stack one by one
    int last_index = StackInfo[stackNo].lastCapacityIndex();
    while (StackInfo[stackNo].isWithinStackCapacity(last_index))
    {
        mainArr[last_index] = mainArr[previousIndex(last_index)];
        last_index = previousIndex(last_index);
    }

    // Adjust current stack's info
    mainArr[StackInfo[stackNo].startIndex] = 0;                               // Clear item
    StackInfo[stackNo].startIndex = nextIndex(StackInfo[stackNo].startIndex); // Move startIndex
    StackInfo[stackNo].capacity--;                                            // Shrink Capacity
}

// Expand the current stack by shifting over other stacks
void Stacks::expand(int stackNo)
{
    shift((stackNo + 1) % numStacks);
}

// Adjust the given index to be within the range of 0 to arr.length-1
int Stacks::adjustIndex(int index)
{
    int max = N;
    return (((index % max) + max) % max);
}

int Stacks::previousIndex(int index)
{
    return (adjustIndex(index - 1));
}

int Stacks::nextIndex(int index)
{
    return (adjustIndex(index + 1));
}

int main()
{
    int numStacks = 3;
    int defaultSize = 5;

    N = numStacks * defaultSize;

    Stacks *ms = new Stacks(numStacks, defaultSize);

    ms->push(0, 15);
    ms->push(0, 23);
    ms->push(0, 49);
    ms->push(0, 57);
    ms->push(0, 11);
    ms->push(0, 68);

    ms->push(1, 88);
    ms->push(1, 83);
    ms->push(1, 76);

    ms->push(2, 22);
    ms->push(2, 33);
    ms->push(2, 44);

    ms->displayStacks();

    cout << "\nAfter Poppin'...";

    ms->pop(1);
    ms->pop(1);
    ms->pop(0);

    ms->displayStacks();
}