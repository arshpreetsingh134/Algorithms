#include <iostream>
#include <exception>
using namespace std;

class MyException : public exception
{
public:
    const char *what() const throw()
    {
        return "\nArray index out of bounds...";
    }
};

template <typename T>
class DynamicArray
{
    T *A;         // initialize an array pointer of type T
    int len = 0;  // current size of array (acc to the user)
    int capacity; // initial array capacity

public:
    DynamicArray()
    {
        this->capacity = 0; // Default Capacity
    }

    DynamicArray(int capacity)
    {
        this->capacity = capacity;
        this->A = new T[capacity];
    }

    int returnSize()
    {
        return len;
    }

    int returnCapacity()
    {
        return capacity;
    }

    bool isEmpty()
    {
        return returnSize() == 0;
    }

    // Fetch a value from the particular index in the array
    T get(int index)
    {
        return A[index];
    }

    // Set the value of a particular index in the array
    void set(int index, T val)
    {
        A[index] = val;
    }

    // Deletes all elements of the array
    void clear()
    {
        for (int i = 0; i < len; i++)
            A[i] = (T)0;

        delete[] A;
        this->len = 0;
        this->capacity = 0;
    }

    // Add an element inside the Dynamic Array
    void add(T elem)
    {
        // Time to resize!
        if (len + 1 > capacity)
        {
            if (capacity == 0)
                capacity = 1;
            else
                capacity *= 2; // Double the size of the array if length exceeds the capacity

            // create a new array which is double the size of the old one
            T *new_Arr = new T[capacity];

            // copy the contents of the old array to the new one
            for (int i = 0; i < len; i++)
                new_Arr[i] = A[i];

            // update the pointer
            A = new_Arr;
        }

        // increment the size by one
        len += 1;

        // insert the element to the new (or same) array
        A[len - 1] = elem;
    }

    // Remove an element at the specified index in the array
    T removeAt(int index)
    {
        try
        {
            if (index >= len || index <= 0)
            {
                MyException e;
                throw e;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        T *new_Arr = new T[len - 1];

        T data = A[index];
        for (int i = 0, j = 0; i < len; i++, j++)
            if (i == index) // Skip over the "remove_index" by fixing j temporarily
                j--;
            else
                new_Arr[j] = A[i];

        // update the pointer
        A = new_Arr;

        // decrease the capacity as well as the size of the array
        capacity = --len;
        return data;
    }

    // Find the index of the specific element
    int indexOf(T elem)
    {
        for (int i = 0; i < len; i++)
            if (A[i] == elem)
                return i;

        return -1;
    }

    // Check whether an element is present inside the array
    bool contains(T elem)
    {
        return (indexOf(elem) != -1);
    }

    // Print the array
    void printArray()
    {
        cout << "\nArray elements are: ";
        for (int i = 0; i < len; i++)
            cout << A[i] << " ";
        cout << "\nSize & Capacity of the array is: " << returnSize() << " " << returnCapacity() << endl;
    }
};

int main()
{
    DynamicArray<int> *da = new DynamicArray<int>();
    cout << "\nSize & Capacity of the array is: " << da->returnSize() << " " << da->returnCapacity() << endl;

    da->add(13);
    da->add(26);
    da->add(39);
    da->add(52);
    da->add(65);
    da->add(78);

    da->printArray();

    da->removeAt(10);
    da->removeAt(2);

    da->printArray();

    da->add(91);
    da->printArray();

    da->clear();

    da->printArray();
}