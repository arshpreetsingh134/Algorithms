// Hash Table Implemmentation using Separate Chaining in C++

// Hash table (also, hash map) is a data structure that basically maps keys to values.
// A hash table uses a hash function to compute an index into an array of buckets or
// slots, from which the corresponding value can be found.

#define CAPACITY 50000 // Size of the Hash Table
#include <iostream>
#include <string.h>
using namespace std;

// Hash Node Data Structure
typedef struct HashItem HashItem;
struct HashItem
{
    char *key;
    char *value;

    // Constructor to create a new Hash Table item
    HashItem(char *key, char *value)
    {
        this->key = new char[strlen(key) + 1];
        this->value = new char[strlen(value) + 1];

        strcpy(this->key, key);
        strcpy(this->value, value);
    }

    // Destructor for freeing memory
    ~HashItem()
    {
        delete this;
    }
};

//********************** Linked List Implementation **********************//
struct Node
{
    HashItem *val; // DS for current item at a given index
    Node *next;    // Pointer to next item at the same index

    // Constructor for initializing Node
    Node(HashItem *val)
    {
        this->val = val;
        this->next = NULL;
    }

    ~Node()
    {
        delete this;
    }
};

class LinkedList
{
    Node *head;
    Node *tail;
    int length;

public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    ~LinkedList()
    {
        delete head;
        delete tail;
    }

    Node *get(int index)
    {
        Node *curr_node = head;
        int i = 0;
        while (i != index)
        {
            if (curr_node == NULL)
                return NULL;

            curr_node = curr_node->next;
            i++;
        }

        return curr_node;
    }

    Node *getHead()
    {
        return head;
    }

    void ll_insert(HashItem *val)
    {
        Node *new_node = new Node(val);

        if (tail != NULL)
            tail->next = new_node;

        tail = new_node;
        length++;
        if (length == 1)
            head = tail;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void ll_delete(int index)
    {
        Node *curr_node = head;
        Node *prev_node = NULL;

        int i = 0;
        while (i != index)
        {

            if (curr_node == NULL)
                return;
            prev_node = curr_node;
            curr_node = curr_node->next;
        }

        if (prev_node)
            prev_node->next = curr_node->next;
        
        if(curr_node==head)
            head = curr_node->next;

        curr_node = NULL;
        delete curr_node;

        if (curr_node == NULL)
            cout << "\n\nDeleted\n";
    }

    void deleteAtKey(char *key)
    {
        Node *curr = head;
        Node *prev = NULL;

        cout << head->val->key;

        while (curr)
        {
            if (strcmp(curr->val->key, key) == 0)
            {

                if (prev == NULL)
                {
                    cout << "Delete22";
                    // First element of the chain. Remove the chain
                    ll_delete(0);
                    return;
                }
                else
                {
                    cout << "Delete11 ";
                    // This is somewhere in the chain
                    prev->next = curr->next;
                    curr->next = NULL;
                    curr->~Node();
                    // buckets[index] = head;
                    return;
                }
            }
            curr = curr->next;
            prev = curr;
        }
    }
};

//********************** Hash Table Data Structure **********************//

class HashTable
{
private:
    HashItem **items;     // Array of pointers to the Hash Items
    LinkedList **buckets; // Array of pointers to the buckets
    int size;             // Current size of Table
    int count;            // Elements in Hash Table

    // Hash Function, calculating the mod of sum of ASCII values in a string
    // Returns an index within the capacity of Hash Table
    // Collision will take place between different strings such as
    // “Hel” and “Cau”, since they have the same ASCII value.
    unsigned long hash_function(char *str)
    {
        unsigned long i = 0;
        for (int j = 0; str[j]; j++)
        {
            // Sum of ASCII values
            i += str[j];
        }
        return i % CAPACITY;
    }

    // Handling Collisions- Chaining
    void handle_collision(HashItem *item, unsigned long index)
    {
        LinkedList *list = buckets[index];

        if (list == NULL)
            list = new LinkedList();

        list->ll_insert(item);
        buckets[index] = list;
    }

public:
    // Creates a Hash Table of a given size by allocating the
    // reqd. memory and setting all its items to NULL initially
    HashTable(int size)
    {
        this->size = size;
        this->count = 0;

        this->items = new HashItem *[size];     // List of items in the table
        this->buckets = new LinkedList *[size]; // List of buckets (in case of 2 or more items) in the table

        // Initialize all items as NULL (by default)
        for (int i = 0; i < size; i++)
            this->items[i] = NULL;

        // Initialize all buckets as NULL (by default)
        for (int i = 0; i < size; i++)
            this->buckets[i] = NULL;
    }

    // Destructor for freeing memory
    ~HashTable()
    {
        delete[] this->items;
        delete[] this->buckets;
        delete this;
    }

    // Insert into Hash Table
    void hashInsert(char *key, char *value)
    {
        // Compute the index where value is to be inserted,
        // using Hash Function
        unsigned long index = hash_function(key);

        HashItem *new_item = new HashItem(key, value);
        HashItem *curr_item = items[index];

        // If Key doesn't exist at the given index
        if (curr_item == NULL)
        {
            // Check if Hash Table already full
            if (count == size)
            {
                cout << "\nHash Table is full!";
                return;
            }

            // If not, insert the item in the table
            // and increment the count
            items[index] = new_item;
            count++;
        }

        // If Key already exists at given index
        else
        {
            // CASE 1: If Duplicate of the Key Found, Update Value
            if (strcmp(curr_item->key, key) == 0)
            {
                strcpy(items[index]->value, value);
                return;
            }

            // CASE 2: Handle Collisions by creating a Linked List
            else
            {
                handle_collision(new_item, index);
                return;
            }
        }
    }

    // Deletes an item from the table, given key
    void hashDelete(char *key)
    {
        unsigned long index = hash_function(key);
        HashItem *item = items[index];
        LinkedList *hlist = buckets[index];

        if (item == NULL)
        {
            // Does not exist. Return
            return;
        }
        else
        {

            if (hlist == NULL && strcmp(item->key, key) == 0)
            {
                // No collision chain. Remove the item
                // and set table index to NULL
                items[index] = NULL;
                items[index]->~HashItem();
                count--;
                return;
            }
            else if (hlist != NULL)
            {

                // Collision Chain exists
                if (strcmp(item->key, key) == 0)
                {
                    // Remove this item and set the head of the list
                    // as the new item

                    items[index]->~HashItem();                                                 // First, free the memory
                    Node *first_node = hlist->getHead();                                       // Now, fetch the head of the LinkedList at current index
                    first_node->next = NULL;                                                   // Free the unneeded memory, i.e, of the "next" pointer of the Node
                    items[index] = new HashItem(first_node->val->key, first_node->val->value); // Assign the head of LL to item
                    first_node->~Node();

                    buckets[index]->ll_delete(0); // Delete the already inserted first node from the LinkedList
                    return;
                }

                // Collision chain exists and key to be deleted is in that chain
                buckets[index]->deleteAtKey(key);
            }
        }
    }

    // Search Items in the Hash Table, return NULL if it doesn't exist
    char *searchItem(char *key)
    {
        unsigned long index = hash_function(key);
        HashItem *item = items[index];
        //cout<<index<<" "<<item->value<<" "<<buckets[index]->getHead()->val->key;
        Node *bucket = NULL;

        if (buckets[index])
            bucket = buckets[index]->getHead();

        //cout<<bucket->val->key;

        // Ensure that we move to a non-NULL item
        while (item != NULL)
        {
            if (strcmp(item->key, key) == 0)
                return item->value;
            if (bucket == NULL)
                return NULL;

            item = bucket->val;
            bucket = bucket->next;
        }
        return NULL;
    }

    // Search for a key and print it's value
    void print_search(char *key)
    {
        char *val;
        if ((val = searchItem(key)) == NULL)
        {
            cout << "\nKey " << key << " doesn't exist." << endl;
            return;
        }
        cout << "\nKey: " << key << " , Value: " << val << endl;
    }

    // Print Hash Table
    void print_table()
    {
        cout << "\n---------------------\n    Hash Table\n---------------------";
        for (int i = 0; i < size; i++)
            if (items[i])
            {
                cout << endl
                     << "Index: " << i << " , Key: " << items[i]->key
                     << " , Value: " << items[i]->value;

                // If more than one items are present at a given index in the table,
                // look for them in the bucket (LinkedList) of that index
                if (buckets[i])
                {
                    Node *head = buckets[i]->getHead();
                    while (head)
                    {
                        cout << " --> "
                             << "Key: " << head->val->key << " , Value: " << head->val->value;
                        head = head->next;
                    }
                }
            }
        cout << "\n------------------------";
    }
};

int main()
{
    HashTable *table = new HashTable(CAPACITY);

    char s1[] = "Name", s2[] = "Arshpreet", s3[] = "Branch", s4[] = "CSE", s5[] = "UID", s6[] = "18BCS6570";
    char s7[] = "Hel", s8[] = "Demo1", s9[] = "Cau", s10[] = "Demo2";

    table->hashInsert(s1, s2);
    table->hashInsert(s3, s4);
    table->hashInsert(s5, s6);
    table->hashInsert(s7, s8);
    table->hashInsert(s9, s10);

    table->print_search(s1);

    table->print_table();

    // hashDelete doesn't work for s7
    table->hashDelete(s3);

    table->print_table();
}
