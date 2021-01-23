// Implementing Minimum Priority Queue using Binary Min-Heap

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>     // For std::floor
#include <algorithm> // For std::max, std::iter_swap

using namespace std;

class prqueue
{
    int heapSize = 0;             // No. of elements currently in the heap
    // int heapCapacity = 0;         // The internal capacity of the heap
    vector<int> heap;             // A Dynamic list to keep track of the elements in the min-heap
    map<int, set<int>> hashtable; // A Hash Map that keeps track of the possible indices for a
    // particular node value found inside the heap

    // Top-down Node Sink (O(nlgn))
    void sink(int node)
    {
        while (true)
        {
            int left = 2 * node + 1;
            int right = 2 * node + 2;
            int smallest = left;

            // Assign the smallest value out of left and
            // right to the 'smallest'
            if (right < heapSize && heap[left] > heap[right])
                smallest = right;

            // Stop if we're outside the bounds of tree or
            // stop if we can't sink k anymore
            if (left >= heapSize || heap[smallest] > heap[node])
                break;

            // Swap the values at indices k & largest
            // inside the heap

            hashtable[heap[node]].erase(node);
            hashtable[heap[smallest]].erase(smallest);
            hashtable[heap[node]].insert(smallest);
            hashtable[heap[smallest]].insert(node);
            iter_swap(heap.begin() + node, heap.begin() + smallest);

            node = smallest;
        }
    }

    // Bottom-up Node Swim (O(nlog(n)))
    void swim(int node)
    {

        if (node > heapSize)
            return;

        int parent = (node - 1) / 2;

        // Keep swimming upwards while we have not reached
        // the root and while we are still less than our parent
        while (node > 0 && heap[node] < heap[parent])
        {
            hashtable[heap[node]].erase(node);
            hashtable[heap[parent]].erase(parent);
            hashtable[heap[node]].insert(parent);
            hashtable[heap[parent]].insert(node);
            iter_swap(heap.begin() + node, heap.begin() + parent);

            node = parent;
            parent = (node - 1) / 2;
        }
    }

    // Remove the element from the Priority Queue,
    // given the index of the Heap's array
    int removeAt(int index)
    {
        if (heap.empty())
            return 0;

        // Swap the value to be deleted with the last
        // value in the heap, and delete the last value
        // Also, remove the node's index from the Hashtable and update it,
        // whenever element is removed from the Priority Queue

        hashtable[heap[index]].erase(index);
        if (hashtable[heap[index]].empty())
            hashtable.erase(heap[index]);

        hashtable[heap[heapSize - 1]].erase(heapSize - 1);
        hashtable[heap[heapSize - 1]].insert(index);
        iter_swap(heap.begin() + index, heap.end() - 1);
        int removed_value = *(heap.end() - 1);

        heap.erase(heap.end() - 1);
        heapSize--;

        if (index == heapSize)
            return removed_value;

        int temp_element = heap[index];

        // Try Sinking...
        sink(index);

        // If Sinking didn't work, try Swimming...
        if (heap[index] == temp_element)
            swim(index);

        return removed_value;
    }

public:
    prqueue() : prqueue(1){};

    prqueue(int size)
    {
        vector<int> new_arr(size);
        heap = new_arr;
    }

    // Priority Queue construction using Heapify
    prqueue(vector<int> &arr)
    {
        heapSize = arr.size();
        // heapCapacity = arr.size();

        // Place all the elements inside the heap,
        // and map them
        for (int i = 0; i < heapSize; i++)
        {
            heap.push_back(arr[i]);
            hashtable[arr[i]].insert(i);
        }

        // Heapify  (O(nlgn))
        for (int i = max(0, (int)(floor(heapSize / 2) - 1)); i >= 0; i--)
        {
            sink(i);
        }
    }

    // Clear the Priority Queue
    void clear()
    {
        heap.erase(heap.begin(), heap.end());
        hashtable.erase(hashtable.begin(), hashtable.end());
        heapSize = 0;
    }

    // Return the current size of the heap
    int size()
    {
        return heapSize;
    }

    // Check if the element is present in the Priority Queue,
    // (Here we use Hashtable instead of Linear Search, as it
    // takes O(1) time)
    bool lookup(int element)
    {
        return hashtable.count(element);
    }

    // Returns the value of node with the lowest priority in the heap
    int peek()
    {
        if (heap.empty())
            return 0;
        return heap[0];
    }

    // Removes the root of the heap
    int poll()
    {
        return removeAt(0);
    }

    // Add an element to the Priority Queue (mustn't be NULL)
    void add(int element)
    {
        heap.push_back(element);
        hashtable[element].insert(heapSize);
        swim(heapSize);
        heapSize++;
    }

    // Delete an element from the Priority Queue (O(lgn))
    // (If the element occurs more than once in the queue,
    // delete the last occurence)
    bool remove(int element)
    {
        if (!hashtable.count(element))
            return false;

        auto itr = hashtable[element].rbegin();
        removeAt(*itr);
        return true;
    }

    // Recursively checks if our heap is still a Minimum Heap
    bool isMinHeap(int k)
    {
        if (k >= heapSize)
            return true;

        int left = 2 * k + 1;
        int right = 2 * k + 2;

        // Make sure that the current node k is less than
        // both of its children left, and right if they exist
        // return false otherwise to indicate an invalid heap
        if (left < heapSize && heap[k] > heap[left])
            return false;
        if (right < heapSize && heap[k] > heap[right])
            return false;

        return isMinHeap(left) && isMinHeap(right);
    }

    // Display the Priority Queue
    void Display()
    {
        if (heap.empty())
        {
            cout << "\nPriority Queue is empty.";
            return;
        }
        for (auto itr : heap)
            cout << itr << " ";
    }

    // Display the Hash Table from nodes to their
    // indices that we've maintained so far
    void mapDisplay()
    {
        map<int, set<int>>::iterator itr;

        for (itr = hashtable.begin(); itr != hashtable.end(); ++itr)
        {
            cout << "\nNode : " << itr->first << endl;
            for (auto i : itr->second)
                cout << i << " ";
        }
    }
};

int main()
{
    vector<int> A{8, 8, 2, 2, 3, 3, 4, 5, 6, 6};
    prqueue p(A);
    p.Display();
    cout << "\nNode with the lowest priority is: " << p.peek();

    cout << "\nAfter deleting the root " << p.poll() << ", the heap is : ";
    p.Display();
    p.mapDisplay();

    int look1 = 68;
    int look2 = 8;
    cout << "\nValue 68 is present? " << p.lookup(look1);
    cout << "\nValue 8 is present? " << p.lookup(look2);

    int remove_val = 3;
    cout << "\n\nAfter removing 3, we get: ";
    p.remove(remove_val);
    p.Display();

    int remove_val2 = 3;
    cout << "\n\nAfter removing 3, we get: ";
    p.remove(remove_val);
    p.Display();

    cout << "\n\nAfter adding 1, our heap is: ";
    p.add(1);
    p.Display();

    cout << "\nChecking whether our Priority Queue follows the Min-Heap property: ";
    cout << p.isMinHeap(0);

    p.mapDisplay();

    p.clear();
    p.Display();
}