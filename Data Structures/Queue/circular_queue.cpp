#include <iostream>
using namespace std;

class Queue
{
    int capacity;
    int *arr;
    int head;
    int tail;

public:
    Queue(int capacity)
    {
        this->capacity = capacity;
        arr = new int[capacity];
        head = -1;
        tail = 0;
    }

    void Enqueue(int x)
    {
        // Check for Overflow
        if(head == tail+1)
        {
            cout<<"Queue Overflow\n";
            return;
        }

        arr[tail] = x;

        if(head==-1)
            head = tail;

        if(tail==capacity-1)
            tail = 0;
        else
            tail=tail+1;
    }

    int Dequeue()
    {
        // Check for Underflow
        if(head==-1)
        {
            cout<<"Queue Underflow\n";
            return -1;
        }

        int del = arr[head];
        arr[head]=0;

        if(head==capacity-1)
            head = 0;
        else
            head=head+1;

        // Queue Empty
        if(head==tail)
            head=-1;

        return del;
    }

    void printQueue()
    {
        // Queue Empty
        if(head==-1)
            return;

        cout<<"head: "<<head<<" tail: "<<tail<<endl;
        
        int i = head;
        while(i!=tail)
        {
            cout<<arr[i]<<" ";
            if(i==capacity-1)
            {
                i=0;
                continue;
            }
            i++;
        }
        
    }
};

int main()
{
    Queue* q = new Queue(5);
    q->Dequeue();

    q->Enqueue(4);
    q->Enqueue(1);
    q->Enqueue(3);
    q->Dequeue();
    //q->Dequeue();
    q->Enqueue(8);
    //q->Enqueue(12);
    q->Dequeue();

    q->printQueue();
}