// Implementing Stack using Max Priority Queue

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class prqueue
{
    int heapSize = 0;
    vector<pair<int, int>> heap;
    int count = 0;

    void sink(int node)
    {
        while (true)
        {
            int left = 2 * node + 1;
            int right = 2 * node + 2;
            int smallest = left;

            if (right < heapSize && heap[left].second < heap[right].second)
                smallest = right;

            if (left >= heapSize || heap[smallest].second < heap[node].second)
                break;

            iter_swap(heap.begin() + node, heap.begin() + smallest);

            node = smallest;
        }
    }

    void swim(int node)
    {
        if (node > heapSize)
            return;

        int parent = (node - 1) / 2;

        while (node > 0 && heap[node].second > heap[parent].second)
        {
            iter_swap(heap.begin() + node, heap.begin() + parent);

            node = parent;
            parent = (node - 1) / 2;
        }
    }

public:
    // prqueue() : prqueue(1){};

    // prqueue(int size)
    // {
    //     pair<int, int> new_arr(size);
    //     heap = new_arr;
    // }

    void push(int element)
    {
        heap.push_back(make_pair(element, count));
        swim(heapSize);
        count++;
        heapSize++;
    }

    void pop()
    {
        // if (heap.empty())
        //     return 0;

        iter_swap(heap.begin(), heap.end() - 1);
        // int removed_value = *(heap.end() - 1).first;

        heap.erase(heap.end() - 1);
        heapSize--;

        sink(0);
    }

    int top()
    {
        return heap[0].first;
    }

    void display()
    {
        cout << endl;
        for (auto i : heap)
            cout << i.first << " ";
    }
};

int main()
{
    prqueue pr;
    pr.push(4);
    pr.push(6);
    pr.push(18);
    pr.push(7);
    cout << endl
         << "Top: " << pr.top();
    pr.display();
    pr.pop();
    pr.display();
    pr.pop();
    cout << endl
         << "Top: " << pr.top();
    pr.display();
    pr.pop();
    pr.display();
}