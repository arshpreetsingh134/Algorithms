// Compareed to the first method we implemented in C++, this one uses less space for
// storing the minSize at each node in the stack (i.e., we use a standalone stack
// specifically for storing the minimum sizes)

import java.util.EmptyStackException;

class Stack<T>
{
    public static class Node<T>
    {
        private T data;
        private Node<T> next;

        public Node(T data)
        {
            this.data = data;
        }
    }

    private Node<T> head;

    public void push(T value)
    {
        Node<T> new_node = new Node<T>(value);
        new_node.next = head;
        head = new_node;
    }

    public T pop()
    {
        if(head==null) throw new EmptyStackException();
        T del_item = head.data;
        head = head.next;
        return del_item;
    }

    public T peek()
    {
        if(head==null) throw new EmptyStackException();
        return head.data;
    }

    public boolean isEmpty()
    {
        return (head==null);
    }
}

public class Stack_Min_2 extends Stack<Integer>
{
    Stack<Integer> size_stack;

    public Stack_Min_2()
    {
        size_stack = new Stack<Integer>();
    }

    public void push(int value)
    {
        if(value<=min())
            size_stack.push(value);

        super.push(value);
    }

    public Integer pop()
    {
        int value = super.pop();
        if(value==min())
            size_stack.pop();
        return value;
    }

    public int min()
    {
        if(size_stack.isEmpty())
            return Integer.MAX_VALUE;

        return size_stack.peek();
    }

    public static void main(String[] args)
    {
        Stack_Min_2 st = new Stack_Min_2();
        
        st.push(4);
        st.push(8);
        st.push(2);
        st.push(10);
        st.push(1);

        System.out.println("\nValue " + st.pop() + " popped from stack.");
        System.out.println("\nValue " + st.pop() + " popped from stack.");
    
        System.out.println("\nMinimum in the stack: "+st.min());
    }
}