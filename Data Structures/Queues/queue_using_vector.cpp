// Implementation of Queue using Vector
#include <iostream>
#include <vector>
using namespace std;

// Adds an element at the end
void Enqueue(vector<int> &queue, int item)
{
    queue.push_back(item);
}

// Removes the first element
int Dequeue(vector<int> &queue)
{
    int first = queue[0];
    queue.erase(queue.begin());
    return first;
}

void display(vector<int> queue)
{
    for (auto i : queue)
    {
        cout << i << " ";
    }
}

int main()
{
    vector<int> queue;
    Enqueue(queue, 8);
    Enqueue(queue, 7);
    Enqueue(queue, 3);
    Enqueue(queue, 6);

    cout << endl
         << Dequeue(queue) << " dequeued from Queue\n";

    display(queue);
}