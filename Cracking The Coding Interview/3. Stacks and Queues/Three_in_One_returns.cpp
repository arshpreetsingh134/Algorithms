// Implementing 3 stacks using 1 array- fixed (predetermined) size
#include <iostream>
#include <cmath>
#include <exception>
#define my_sizeof(type) ((char *)(&type + 1) - (char *)(&type))
using namespace std;

class MultiStack
{
    // Sub-class for handling exceptions
    class myException : public exception
    {
    public:
        const char *what() const throw()
        {
            cout << "\nStack Underflow!\n";
        }
    };

    int *values;        // Array of values (the main array to hold 3 stacks)
    int sizeOf(int *);  // Utility Function to calculate size of array
    
    // Sub-class for holding a set of data about each stack
    class StackInfo
    {
        public:
        int start, size, capacity;

        StackInfo(){}

        StackInfo(int start, int capacity)
        {
            this->start = start;        // Index of start of each stack
            this->capacity = capacity;  // Capacity of each stack
        }

        // Check if an index on the full array is within the stack boundaries. 
        // The stack can wrap around to the start of the array
        bool isWithinStackCapacity(int index)
        {
            // If outside of the bounds of array, return false
            if(index<0 || index>=sizeOf(values))
                return false;

            // If index wraps around, adjust it
            int contiguousIndex = index<start?index+sizeOf(values):index;
            int end = start + capacity;
            return start<=contiguousIndex && contiguousIndex<end;
        }

        int lastCapacityIndex()
        {
            return (start+capacity-1);
        }
        
        int lastElementIndex()
        {
            return (start + size - 1);
        }

        // Check if the given stack is full/empty
        bool isFull() { return size == capacity; }
        bool isEmpty() { return size == 0; }
    };

    StackInfo* info;     // Array of 3 stacks (info)
    int sizeOf(StackInfo*); // (same)
    void shift(int);             // Shifting stacks one by one to make more space
    void expand(int);            // Expand stack by shifting over other stacks
    int adjustIndex(int);        // Adjust the given index so as to be within the range
    int previousIndex(int);      // Fetch the previous index in the array
    int nextIndex(int);          // Fetch the next index in the array

public:

    bool allStacksAreFull();    // Check if all stacks are full
    int numElements();          // Returns the no. of items actually present in the array

    // Constructor for creating metadata for all the stacks.
    // We pass the no. of stacks we need (3) and the default
    // size of each stack as parameters
    MultiStack(int num_stacks, int defaultSize)
    {
        // Initiate an array of objects for storing info of 3 stacks
        info = new StackInfo[num_stacks];

        // Fill info for each of the 3 stacks
        for(int i=0; i<num_stacks; i++)
            info[i] = StackInfo(defaultSize*i, defaultSize);

        values = new int[defaultSize*num_stacks];
    }

    // Push value onto stackNo, shifting/ expanding stacks as necessary
    void push(int stackNo, int value)
    {
        // Exception: Stack Overflow
        if (allStacksAreFull())
        {
            cout<<"All 3 Stacks Overflowed!";
            return;
        }

        // If stack is full, expand it
        StackInfo stack = info[stackNo];
        if(stack.isFull())
            expand(stackNo);

        // Find the index of topmost element of the stack and increment it
        stack.start++;
        values[stack.lastElementIndex()] = value;
    }

    // Remove value from the stack
    int pop(int stackNo)
    {
        StackInfo stack = info[stackNo];
        try
        {
            if (stack.isEmpty())
                throw new myException();
            
            // Remove last element from the stack
            int value = values[stack.lastElementIndex()];
            values[stack.lastElementIndex()] = 0;   // Clear Item
            stack.size--;
            return value;
        }
        catch(const std::exception* e)
        {
            e->what();
        }  
    }

    // Fetch the top element of stack
    int peek(int stackNo)
    {
        StackInfo stack = info[stackNo];
        return values[stack.lastElementIndex()];
    }
};

// Utility Function for calculating the size of an array
int MultiStack::sizeOf(int arr[])
{
    return my_sizeof(arr) / my_sizeof(arr[0]);
}

int MultiStack::sizeOf(StackInfo arr[])
{
    return my_sizeof(arr) / my_sizeof(arr[0]);
}

// Returns the no. of items actually present in the array
int MultiStack::numElements()
{
    int size = 0;
    for (int i = 0; i < sizeOf(info); i++)
        size+=info[i].size;
    return size;
}

// Check if all stacks are full
bool MultiStack::allStacksAreFull()
{
    return sizeOf(values) == numElements();
}

// Shift items in stack over by one element. If we have available capacity, 
// then we'll end up shrinking the stack by one element. If we don't have 
// available capacity, then we'll need to shift the next stack over too.
void MultiStack::shift(int stackNo)
{
    cout<<"\n///SHIFTING STACK NO."<<stackNo;
    StackInfo stack = info[stackNo];

    // If this stack is at its full capacity, then move the next
    // stack over by one element
    if(stack.size >= stack.capacity)
    {
        int nextStack = (stackNo+1)%sizeOf(info);
        shift(nextStack);       // Shift the subsequent stacks recursively
        stack.capacity++;      // Claim index that the next stack lost
    }

    // Shift all elements in stack one-by-one
    int index = stack.lastCapacityIndex();
    while(stack.isWithinStackCapacity())
    {
        values[index] = values[previousIndex[index]];
        index = previousIndex(index);
    }

    // Adjust stack data
    values[stack.start] = 0;   // Clear the item for use by previous stack
    stack.start = nextIndex(stack.start); // Shift the start pointer to point to next position
    stack.capacity--;
}

// Expand the current stack by shifting over other stacks
void MultiStack::expand(int stackNo)
{
    shift((stackNo+1)%sizeOf(info));
    info[stackNo].capacity++;
}

// Adjust the given index to be within the range of 0 to arr.length-1
int MultiStack::adjustIndex(int index)
{
    // C++'s mod operator can return neg values . For example, (-11 % 5) will
    // return -1, not 4. We actually want the value to be 4 (since we're wrapping 
    // around the index)
    int arr_length = sizeOf(values);
    return ((index%arr_length)+arr_length)%arr_length;
}

// Get index after the given index, adjusted for wraparound
int MultiStack::nextIndex(int index)
{
    return adjustIndex(index + 1);
}

// Get index before the given index, adjusted for wraparound
int MultiStack::previousIndex(int index)
{
    return adjustIndex(index-1);
}



int main()
{
    MultiStack* ms = new MultiStack(3, 5);

    ms->push(1, 15);
    ms->push(0, 22);
    ms->push(2, 28);
    ms->push(1, 55);

    cout<<"Topmost element of the stack: "<<ms->peek(1);
}