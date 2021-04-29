// Hash Table Implemmentation using "Separate Chaining" in Java

import java.util.*;

// DS for the key-value pairs in Hash Table
class Entry<K, V> {
    int hash;
    K key;
    V value;

    public Entry(K key, V value) {
        this.key = key;
        this.value = value;
        this.hash = key.hashCode();
        // Note: hashCode() is an inbuilt Java class method which
        // returns a hash code value for a type value specified in the
        // method argument.
    }

    // Check whether the given key-value pair differs from that of the current one
    public boolean equals(Entry<K, V> other) {
        // First check for the hash values of both pairs
        // If not equal, return false
        // If equal, check if the keys are equal or not
        if (hash != other.hash)
            return false;
        return key.equals(other.key);
    }

    @Override
    public String toString() {
        return key + " => " + value;
    }
}

// Hash Table Data Structure
public class Hash_Table_SC<K, V> implements Iterable<K> {
    private static final int DEFAULT_CAPACITY = 3; // Default Capacity of the HT
    private static final double DEFAULT_LOAD_FACTOR = 0.75;
    // When the load factor exceeds 75% of the current HT capacity,
    // increase the HT's size by double

    private double maxLoadFactor;
    private int capacity, threshold, size = 0;
    private LinkedList<Entry<K, V>>[] table; // Array of lists of key-value pairs

    public Hash_Table_SC() {
        this(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
    }

    public Hash_Table_SC(int capacity) {
        this(capacity, DEFAULT_LOAD_FACTOR);
    }

    public Hash_Table_SC(int capacity, double maxLoadFactor) {
        if (capacity < 0)
            throw new IllegalArgumentException("Capacity can't be negative");
        if (maxLoadFactor <= 0 || Double.isNaN(maxLoadFactor) || Double.isInfinite(maxLoadFactor))
            throw new IllegalArgumentException("Illegal maxLoadFactor");

        this.capacity = Math.max(DEFAULT_CAPACITY, capacity);
        this.maxLoadFactor = maxLoadFactor;
        threshold = (int) (this.capacity * maxLoadFactor); // If HT reaches this threshold, its time to expand the table
        table = new LinkedList[this.capacity];
    }

    // Returns the no. of elements currently in the Hash Table
    public int size() {
        return size;
    }

    // Check whether the Hash Table is empty or not
    public boolean isEmpty() {
        return size == 0;
    }

    // Converts a Hash Value to an index. Essentially, this strips the
    // negative sign and places the hash value in the domain [0, capacity)
    private int normalizeIndex(int keyHash) {
        // The constant 0x7FFFFFFF is a 32-bit integer in hexadecimal with all but the
        // highest bit set.
        // When you use % on negative value, you get a negative value. There are no
        // negative buckets
        // so to avoid this you can remove the signed bit (the highest bit) and one way
        // of doing this
        // is to use a mask e.g. x & 0x7FFFFFFF which keeps all the bits except the top
        // one
        return (keyHash & 0x7FFFFFFF) % capacity;

        // there is another way...
        // return (Math.abs(keyHash)%capacity);
    }

    // Clear all the contents of the Hash Table
    public void clear() {
        Arrays.fill(table, null);
        size = 0;
    }

    // Check whether the key is present inside the Hash Table
    public boolean containsKey(K key) {
        int bucketIndex = normalizeIndex(key.hashCode());
        return (bucketSeekEntry(bucketIndex, key) != null);
    }

    // Add a value at a particular key inside the Hash Table
    public V add(K key, V value) {
        if (key == null)
            throw new IllegalArgumentException("Null Key");
        Entry<K, V> new_pair = new Entry<K, V>(key, value);
        int bucketIndex = normalizeIndex(new_pair.hash);
        return bucketInsertEntry(bucketIndex, new_pair);
    }

    // Gets a key's value from the map and returns the value
    public V get(K key) {
        if (key == null)
            return null;
        int bucketIndex = normalizeIndex(key.hashCode());
        Entry<K, V> entry = bucketSeekEntry(bucketIndex, key);

        // If the given key is present in the bucket, return its
        // corresponding value, else return null
        if (entry != null)
            return entry.value;
        return null;
    }

    // Removes a key from the map and returns the value.
    // NOTE: returns null if the value is null AND also returns
    // null if the key does not exists.
    public V remove(K key) {

        if (key == null)
            return null;
        int bucketIndex = normalizeIndex(key.hashCode());
        return bucketRemoveEntry(bucketIndex, key);
    }

    // Resizes the internal table holding thr buckets of entries to twice the
    // capacity
    private void resizeTable() {
        capacity *= 2;
        threshold = (int) (capacity * maxLoadFactor);

        LinkedList<Entry<K, V>>[] newTable = new LinkedList[capacity];

        // Copy the values from the old table to the new table
        for (int i = 0; i < table.length; i++) {
            if (table[i] != null) {
                for (Entry<K, V> entry : table[i]) {
                    int bucketIndex = normalizeIndex(entry.hash);
                    if (newTable[bucketIndex] == null)
                        newTable[bucketIndex] = new LinkedList<>();
                    newTable[bucketIndex].add(entry);
                }

                // Avoid memory leaks
                table[i].clear();
                table[i] = null;
            }
        }

        // Update the pointer to the new table
        table = newTable;
    }

    // Finds and returns a particular entry in a given bucket, if it exists,
    // else return null
    private Entry<K, V> bucketSeekEntry(int bucketIndex, K key) {
        if (key == null)
            return null;
        LinkedList<Entry<K, V>> bucket = table[bucketIndex];

        if (bucket == null)
            return null;

        for (Entry<K, V> entry : bucket)
            if (entry.key.equals(key))
                return entry;
        return null;
    }

    // Inserts an entry in a given bucket only if the entry does not already
    // exist in the given bucket, but if it does then update the entry value
    // If the entry was newly inserted, return null, else return the previous
    // entry's value
    private V bucketInsertEntry(int bucketIndex, Entry<K, V> entry) {
        // If no entry has been inserted yet, create a new LL inside the bucket
        if (table[bucketIndex] == null)
            table[bucketIndex] = new LinkedList<>();

        LinkedList<Entry<K, V>> bucket = table[bucketIndex];

        // Check for an existing entry at the current bucket for the given key
        Entry<K, V> existing_entry = bucketSeekEntry(bucketIndex, entry.key);

        // If the key doesn't already exist, add a brand new entry to the current bucket
        if (existing_entry == null) {
            bucket.add(entry);

            // If the current HT reaches a threshold, expand its capacity
            if (++size > threshold)
                resizeTable();

            return null; // Use null to indicate that there was no previous entry, i.e.,
                         // entry was newly inserted
        }

        // If the key is found, update the value for the given key
        else {
            V oldVal = existing_entry.value;
            existing_entry.value = entry.value;
            return oldVal;
        }
    }

    // Removes an entry from a given bucket if it exists
    private V bucketRemoveEntry(int bucketIndex, K key) {
        Entry<K, V> entry = bucketSeekEntry(bucketIndex, key);
        if (entry != null) {
            LinkedList<Entry<K, V>> links = table[bucketIndex];
            links.remove(entry);
            --size;
            return entry.value;
        } else
            return null;
    }

    // Return the list of keys found within the Hash Table
    public List<K> keys() {
        List<K> keys = new ArrayList(size());

        for (LinkedList<Entry<K, V>> bucket : table)
            if (bucket != null)
                for (Entry<K, V> entry : bucket)
                    keys.add(entry.key);
        return keys;
    }

    // Return the list of values found within the Hash Table
    public List<K> values() {
        List<K> values = new ArrayList(size());

        for (LinkedList<Entry<K, V>> bucket : table)
            if (bucket != null)
                for (Entry<K, V> entry : bucket)
                    values.add(entry.value);
        return values;
    }

    // Return an iterator to iterate over all the keys in this map
    @Override
    public java.util.Iterator<K> iterator() {
        final int elementCount = size();
        return new java.util.Iterator<K>() {

            int bucketIndex = 0;
            java.util.Iterator<Entry<K, V>> bucketIter = (table[0] == null) ? null : table[0].iterator();

            @Override
            public boolean hasNext() {

                // An item was added or removed while iterating
                if (elementCount != size)
                    throw new java.util.ConcurrentModificationException();

                // No iterator or the current iterator is empty
                if (bucketIter == null || !bucketIter.hasNext()) {

                    // Search next buckets until a valid iterator is found
                    while (++bucketIndex < capacity) {
                        if (table[bucketIndex] != null) {

                            // Make sure this iterator actually has elements -_-
                            java.util.Iterator<Entry<K, V>> nextIter = table[bucketIndex].iterator();
                            if (nextIter.hasNext()) {
                                bucketIter = nextIter;
                                break;
                            }
                        }
                    }
                }
                return bucketIndex < capacity;
            }

            @Override
            public K next() {
                return bucketIter.next().key;
            }

            @Override
            public void remove() {
                throw new UnsupportedOperationException();
            }
        };
    }

    // Returns a string representation of this hash table
    @Override
    public String toString() {

        StringBuilder sb = new StringBuilder();
        sb.append("{");
        for (int i = 0; i < capacity; i++) {
            if (table[i] == null)
                continue;
            for (Entry<K, V> entry : table[i])
                sb.append(entry + ", ");
        }
        sb.append("}");
        return sb.toString();
    }

    public static void main(String[] args) {
        Hash_Table_SC<String, Integer> ht = new Hash_Table_SC<String, Integer>(5);

        ht.add("Hello", 4);
        ht.add("World", 8);
        ht.add("to", 66);
        ht.add("Java", 88);

        ht.add("Java", 89);

        System.out.println(ht.toString());

        ht.remove("Java");

        System.out.println(ht.toString());
    }
}