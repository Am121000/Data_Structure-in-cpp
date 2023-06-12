#Linked List
A linked list is a linear data structure where elements, called nodes, are connected to form a sequence. Each node contains two components: the data itself and a reference (or link) to the next node in the sequence. The first node is called the head of the linked list, and the last node points to NULL, indicating the end of the list.

## Unlike arrays, linked lists do not require contiguous memory allocation. Each node can be dynamically allocated in memory, and they are connected by their references rather than physical placement. This flexibility allows for efficient insertion and deletion operations at any position within the list.

There are two main types of linked lists: singly linked lists and doubly linked lists.

Singly Linked List: In a singly linked list, each node has a reference to the next node in the sequence. The last node points to NULL to indicate the end of the list. Traversing a singly linked list starts from the head and follows the next pointers until reaching NULL.

Doubly Linked List: In a doubly linked list, each node has two references: one to the next node and one to the previous node. This allows for traversal in both directions. The first node's previous reference points to NULL, and the last node's next reference points to NULL.

Linked lists offer several advantages and disadvantages:

## Advantages:

Dynamic size: Linked lists can grow or shrink dynamically by allocating or deallocating nodes.
Efficient insertion and deletion: Adding or removing nodes in a linked list involves adjusting a few references, making these operations efficient.
Flexibility: Linked lists can be easily modified to accommodate changes in the data structure.

## Disadvantages:

Sequential access: Unlike arrays, accessing elements in a linked list sequentially can be slower since each node requires traversing the references.
Additional memory: Linked lists require extra memory to store the references for linking the nodes together.
Random access: Directly accessing nodes at a specific position in the list requires traversing through the preceding nodes, which can be slower compared to arrays.
Linked lists are commonly used in scenarios where efficient insertion and deletion operations are crucial, or when the size of the data structure needs to be dynamic. They serve as fundamental building blocks for more complex data structures like stacks, queues, and hash tables.
