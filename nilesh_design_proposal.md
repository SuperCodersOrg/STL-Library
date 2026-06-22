# Design Proposal

# Section 1 - Public API



Three data structures will be implemented manually:



* **DynamicArray** – A dynamically resizable array that stores elements in contiguous memory and provides efficient random access.



* **LinkedList** – A singly linked list consisting of nodes connected through pointers, allowing efficient insertion and deletion operations.



* **HashMap** – A key-value data structure that uses hashing to provide efficient average-case insertion, deletion, and lookup operations.



The APIs are designed to provide commonly used operations while keeping the implementation simple and modular.
.

## DynamicArray

```cpp
template<typename T> class DynamicArray{
    public:

    DynamicArray();// Constructor
    DynamicArray(const DynamicArray& other); //Copy Constructor
    DynamicArray(DynamicArray&& other); // Move Constructor
    ~DynamicArray(); //Destructor
    void push_back(T value); //Add value at last
    void insert(int index, T value); //Add value at given index
    void remove(int index);// Delete value by index
    void pop_back(); // Delete last element
    T get(int index);// return value at given index
    int size(); // return number of elements inserted
    int capacity();// returns total capacity of array
    void clear(); // remove all elements
};
```
## LinkedList  


```cpp   
template<typename T>class LinkedList{

    private:
    struct Node{
        T data;
        Node*next;
        Node(T val);
    }
    public:
    Node*head=nullptr;
    Node*tail=nullptr;
    int size=0;
    LinkedList(); //Constructor
    LinkedList(const LinkedList& other); // Copy Constructor
    LinkedList(LinkedList&& other); // Move Constructor 
    ~LinkedList(); // Destructor
    void insertFront(T value); //Insert value at front
    void deleteFront(); // Delete first value
    void insert(int pos, T value); //Insert value at given position
    void append(T value); // Insert value at last
    bool exists(T value); //returns true of value exists otherwise returns false 
    int size(); //return size of the linkedlist
    void reverse()// reverse the LinkedList
    void print(); // print the linkedlist
};
```

The current implementation uses a **singly linked list** because it provides a simple structure and satisfies the requirements of the project. However, the design remains *flexible*. If future requirements demand more efficient *bidirectional traversal* or *frequent operations* at both ends of the list, the implementation may be extended to a **doubly linked** list. Such a change can be made without affecting the public interface significantly, allowing the data structure to evolve based on performance considerations and project needs.



## HashMap

```cpp
template <typename K , typename V> class HashMap {
    
    public:
    HashMap(); // Constructor
    HashMap(const HashMap& other); // Copy Constructor
    HashMap& operator=(const HashMap& other); // Handling assignment operator
    ~HashMap(); // Destructor
    void insert(K key,V value); // Insert key-value pair
    V get(K key); //return value by key
    bool exists(const K& key) const; //returns true if key exists
    void remove(K key); // delete key-value pair
    int size() const; // returns the size of hashtable
    int capacity() const; // returns the total capacity of hash table
    float loadFactor() const; // returns the value of load factor
    void clear(); // clear the entire hashmap
    
};
```

**Templates** are used in all data structures to make them generic and reusable. They allow a single implementation to work with different data types without duplicating code, while also providing compile-time type safety and efficient performance.

This design also improves scalability, as *new methods and functionalities can be added* without creating separate versions for each data type, making the data structures more flexible and maintainable.

# Section 2 - Internal Representation

## Rule of Three

All three data structures allocate memory dynamically. Therefore, each structure follows the Rule of Three by implementing a **destructor**, **copy constructor**, and **copy assignment operator**. These functions ensure proper resource management, prevent `memory leaks`, and provide correct deep copying of dynamically allocated data.

### DynamicArray


DynamicArray stores elements in a contiguous block of memory allocated on the *heap*. Two integer fields are maintained to track the current size and total capacity.

The destructor releases the dynamically allocated array using `delete[]`.

Copy operations perform a **deep copy** by allocating a new array and copying all elements from the source object.


![DynamicArray](Dynamicarray.jpg)
### LinkedList


LinkedList consists of individually allocated nodes connected by *next pointers*. Each node stores a value of type `T` and a pointer to the next node.

The destructor `traverses` the list and deletes every node until the list becomes empty.

Copy operations perform a deep copy by allocating new nodes and duplicating the contents of the source list.


![LinkedList](Linkedlist.jpg)

### HashMap


HashMap uses **separate chaining**. A bucket array stores pointers to *linked lists*, where each node in a chain stores a key and a value of type `T`.

The destructor `traverses` every bucket, deletes all nodes in the chains, and finally releases the bucket array.

Copy operations perform a deep copy by allocating a new bucket array and duplicating all key-value pairs.


![Hashmap1](Hashmap1.jpg)
![Hashmap2](Hashmap2.jpg)

### Copy Operations

All three data structures use **deep copying** for copy operations. During a copy operation, new memory is allocated and the contents of the source object are duplicated into the newly allocated memory.

Shallow copying is avoided because shared memory may lead to `dangling pointers`, `double deletion`, `undefined behavior`, and `program crashes`.


# Section 3 - Complexity Estimates

## DynamicArray

### push_back()

* **Best Case:** O(1)
* **Average Case:** O(1) amortized
* **Worst Case:** O(n)

**Why:** Appending normally places the element at the end of the array in constant time. When the array becomes full, a larger array is allocated and all existing elements are copied, resulting in O(n) time. Since resizing occurs infrequently, the average cost per insertion remains O(1).

### insert(index)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Insertion at the end requires no shifting. Inserting elsewhere requires moving elements to the right.

### remove(index)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Removing the last element is constant time. Otherwise, elements after the removed position must be shifted left.

### pop_back()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The size counter is simply decreased by one.

### get(index)

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** Array indexing directly computes the memory address.

### size()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The size is maintained in a variable.

### capacity()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The capacity is stored in a variable.

### clear()

* **Best Case:** O(n)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** The entire array memory is released using a single delete[] operation.

---

## LinkedList

### insertFront()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The new node becomes the head node.

### deleteFront()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** Only the head pointer is updated.

### insert(pos)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Traversal is required to reach the insertion position.

### contains(value)

* **Best Case:** O(1)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** The value may be found immediately or after scanning the entire list.

### size()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The number of nodes is stored in a variable.

### print()

* **Best Case:** O(n)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Every node must be visited.

---

## HashMap

(Collision handling uses separate chaining.)

### insert()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** Under normal conditions, insertion occurs in a short chain. If all keys hash to the same bucket, the entire chain must be traversed.

### get()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** Hashing provides direct access to the appropriate bucket. In the worst case, all keys may collide into the same bucket, requiring traversal of the entire chain.

### exists()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** Searching is limited to a single chain in average cases, but may require scanning all elements if collisions are excessive.

### remove()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(n)

**Why:** The appropriate bucket is found directly, but collisions may require traversing a long chain.

### size()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The number of stored elements is maintained in a variable.

### capacity()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** The number of buckets is stored in a variable.

### loadFactor()

* **Best Case:** O(1)
* **Average Case:** O(1)
* **Worst Case:** O(1)

**Why:** It is computed using size divided by capacity.

### clear()

* **Best Case:** O(n)
* **Average Case:** O(n)
* **Worst Case:** O(n)

**Why:** Every element stored in the hash table must be deleted. This requires traversing all chains and deleting each node once.



## Section 4 - Design Decision

### DynamicArray

`Proposed design reason`  
2x Resize - It gives amortized O(1) for insertion

`Rejected design reason`  
Append single slot - Gives nearly O(N²) complexity

### LinkedList

`Proposed design reason`    
Singly Linked List - Less memory usage

`Rejected design reason`  
Doubly Linked List - More memory usage

### HashMap

`Proposed design reason`    
Using separate chaining for collision resolution - Easy insertion and deletion
Rehashing after reaching load factor 75% (0.75).

`Rejected design reason`  
Rejected linear probing because primary clustering increases the number of probes and degrades performance.

## Summary

This design prioritizes **simplicity, correctness, and amortized efficiency**. All three structures properly implement the Rule of Three, use deep copying to avoid lifetime bugs, and provide complexity guarantees suitable for typical use cases. Memory diagrams showing heap allocation are submitted separately as required.
