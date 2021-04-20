#include <iostream>
using namespace std;

class Queue
{
    int front, rear, size;
    unsigned capacity;
    int *arr;

    bool isFull()
    {
        return size == capacity;
    }

    bool isEmpty()
    {
        return size == 0;
    }

public:
    /// To create a queue of given capacity.
    // It initializes size of queue as 0
    Queue(unsigned capacity)
    {
        this->capacity = capacity;
        front = 0;
        rear = -1;
        size = -1;
        arr = new int[(capacity * sizeof(int))];
    }

    // To add an item to the queue. It changes rear and size
    void enqueue(int item)
    {
        if (isFull())
        {
            cout << "Queue is full.";
            return;
        }

        rear = rear + 1;
        arr[rear] = item;
        size += 1;
    }

    // To remove an item from queue. It changes front and size
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty";
            return;
        }

        front = (front + 1);
        size -= 1;
    }

    void display()
    {
        if(isEmpty())
        {
            cout<<"\nQueue is empty.";
            return;
        }

        if(isFull())
        {
            cout<<"\nQueue is full.";
            return;
        }

        for (int i = front; i <= rear; i++)
        {
            cout << arr[i] << " ";
        }
    }
};

int main()
{
    Queue *q = new Queue(5);
    q->enqueue(5);
    q->enqueue(8);
    q->enqueue(6);
    q->enqueue(10);
    q->dequeue();
    q->enqueue(22);
    q->enqueue(45);
    q->dequeue();
    q->dequeue();

    q->display();
}