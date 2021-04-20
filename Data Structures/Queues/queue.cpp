// A Linked-List Implementation of a Queue

#include <iostream>
#include <exception>
using namespace std;

// Exception Handling
class MyException
{
    const char *what() const throw()
    {
        return "\nQueue is empty.";
    }
};

// Implementation of a LinkedList
template <typename T>
class MyLinkedList
{
    struct Node
    {
    public:
        T val;
        Node *next;

        /** Initializing the Linked List **/
        Node(T val = 0, Node *next = nullptr)
        {
            this->val = val;
            this->next = next;
        }
    };

    Node *head, *tail;
    int size = 0;

public:
    MyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    T get(T index)
    {
        Node *curr_node = head;
        T i = 0;
        while (i != index)
        {
            if (curr_node)
                curr_node = curr_node->next;
            else
                break;
            i++;
        }

        if (curr_node)
            return curr_node->val;

        return -1;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(T val)
    {
        if (!tail)
            tail = new Node(val);
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }

        // If head is NULL
        if (!head)
            head = tail;
        size++;
    }

    T deleteAtHead()
    {
        try
        {
            if (size == 0)
            {
                MyException e;
                throw e;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        if (size == 1)
        {
            int item = head->val;
            delete head;
            head = NULL;
            size--;
            return item;
        }

        Node *temp = head;
        head = temp->next;
        size--;
        int item = temp->val;
        delete temp;
        return item;
    }

    T peekLast()
    {
        try
        {
            if (!tail)
            {
                MyException e;
                throw e;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return tail->val;
    }

    int returnSize()
    {
        return size;
    }

    void display()
    {
        Node *curr_node = head;
        cout << endl;
        while (curr_node->next != NULL)
        {
            cout << curr_node->val << " ";
            curr_node = curr_node->next;
        }
        cout << curr_node->val;
    }
};

// Implementation of a Queue using a LinkedList
template <typename T>
class Queue
{
    MyLinkedList<T> *list;

public:
    Queue()
    {
        this->list = new MyLinkedList<T>();
    }

    // Create a Queue with an initial element
    Queue(T firstElement)
    {
        Queue();
        list->push(firstElement);
    }

    // Return the size of the queue
    T size()
    {
        return list->returnSize();
    }

    // Check if the queue is empty
    bool isEmpty()
    {
        return size() == 0;
    }

    // Insert an element to the Queue
    void enqueue(T elem)
    {
        list->addAtTail(elem);
    }

    // Delete an element off the Queue
    T dequeue()
    {
        try
        {
            if (isEmpty())
            {
                MyException e;
                throw e;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return list->deleteAtHead();
    }

    // Access the last element of the queue
    // Throws an exception if the queue is empty
    T peek()
    {
        try
        {
            if (isEmpty())
            {
                MyException e;
                throw e;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return list->peekLast();
    }

    void display()
    {
        list->display();
    }
};

int main()
{
    Queue<int> *s = new Queue<int>();

    s->enqueue(4);
    s->enqueue(5);
    s->enqueue(10);
    s->enqueue(48);

    cout << s->dequeue() << " deleted from the Queue.\n";

    cout << s->peek() << " is the last element of the queue.\n";

    s->display();
}