// A Linked-List Implementation of a Stack

#include <iostream>
#include <exception>
using namespace std;

// Exception Handling
class MyException
{
    const char *what() const throw()
    {
        return "\nStack is empty.";
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

    T deleteAtTail()
    {
        Node *curr_node = head;
        int i = 0;
        while (i != size - 2)
        {
            curr_node = curr_node->next;
            i++;
        }
        curr_node->next = NULL;
        T item = tail->val;
        delete tail;
        tail = curr_node;
        size--;
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

// Implementation of a Stack using a LinkedList
template <typename T>
class Stack
{
    MyLinkedList<T> *list;

public:
    Stack()
    {
        this->list = new MyLinkedList<T>();
    }

    // Create a stack with an initial element
    Stack(T firstElement)
    {
        Stack();
        list->push(firstElement);
    }

    // Return the size of the stack
    T size()
    {
        return list->returnSize();
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        return size() == 0;
    }

    // Push an element on the stack
    void push(T elem)
    {
        list->addAtTail(elem);
    }

    // Pop an element off the stack
    T pop()
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

        return list->deleteAtTail();
    }

    // Peek the top of the stack without removing an element
    // Throws an exception if the stack is empty
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
    Stack<int> *s = new Stack<int>();

    s->push(4);
    s->push(5);
    s->push(10);
    s->push(48);

    cout << s->pop() << " deleted from the stack.\n";

    cout << s->peek() << " is the topmost element.\n";

    s->display();
}