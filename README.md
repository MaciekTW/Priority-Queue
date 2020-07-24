# Priority-Queue

## Main function descriptions:

    • PQInit – Creates the new Queue of given size
    • PQEnqueue – Adds a new item to the Queue (returns 1 is succeed)
    • PQEnqueue – Removes an item with highest Priority and returns pointer to the deleted element
    • PQClear – Removes all items from the queue
    • PQRelease - Removes all items and frees the Queue
    • PQPrint – Prints the items of the Queue using inorder traversal
    • PQSetPrior- Changes a priority of the selected item.

## Global.h file

PQInfo structure created inside global.h file allows us to declare any data structure inside our Queue. (For example an Array with two elements as in example)
