#include "queue.h"

/**
 * Creates a queue with a given capacity.
 * @param maxQueueItems: The maximum number of items the queue can hold.
 * @return: The queue.
*/
Queue* createQueue(int maxQueueItems){
    Queue* queue;
    queue = (Queue *)malloc(sizeof(Queue));

    // Initialize the head, tail, and size of the queue to zero, -1, and zero, respectively.
    queue->head = 0;
    queue->tail = -1;
    queue->size = 0;

    // Allocate memory for the items array based on the maximum capacity of the queue.
    queue->items = (int*)malloc(sizeof(int)*maxQueueItems);
    queue->capacity = maxQueueItems;
    
    return queue;
}

/**
 * Removes the front item from the queue.
 * @param queue: The queue to remove from.
 * @return: The item that was removed.
*/
void removeFromQueue(Queue* queue){
    if(queue->size==0){
        printf("The queue has no items!\n");
        return;
    }
    else{
        queue->size--;
        queue->head++;

        // Wrap around to the beginning of the array if the head is at the end of the array.
        if(queue->head==queue->capacity){
            queue->head=0;
        }
    }
    return;
}

/**
 * Gets the front item from the queue.
 * @param queue: The queue to get from.
 * @return: The item that was gotten.
*/
int getFrontOfQueue(Queue* queue){
    if(queue->size==0){
        printf("The queue has no items!\n");
        exit(0);
    }
    return queue->items[queue->head];
}

/**
 * Adds an item to the end of the queue.
 * @param queue: The queue to add to.
 * @param item: The item to add.
*/
void addToQueue(Queue* queue,int item){
    if(queue->size == queue->capacity){
            printf("The queue is at capacity!\n");
    }
    else{
        // Increment the tail and wrap around to the beginning of the array if necessary.
        queue->tail = queue->tail + 1;
        if(queue->tail == queue->capacity)
        {
            queue->tail = 0;
        }

        // Add the new item to the end of the queue and update the size.
        queue->items[queue->tail] = item;
        queue->size++;
    }
}

/**
 * Gets the size of the queue.
 * @param queue: The queue to get the size of.
 * @return: The size of the queue.
*/
int getQueueSize(Queue* queue){
    return queue->size;
}

/**
 * Frees the memory allocated to the queue.
 * @param queue: The queue to free.
*/
void wipeQueue(Queue* queue){
    free(queue->items);
}

/**
 * Prints the queue.
 * @param queue: The queue to print.
 * @return: The queue.
*/
void printQueue(Queue* queue){
    int i;
    for(i=0;i<queue->size;i++){
        printf("%d ",getSpecificItem(queue,i));
    }
}

/**
 * Gets a specific item from the queue.
 * @param queue: The queue to get from.
 * @param n: The index of the item to get.
 * @return: The item that was gotten.
*/
int getSpecificItem(Queue* queue,int n){
    if(n>queue->size){
        return -1;
    }

    // Compute the position of the item based on the head and the requested index.
    int position = queue->head + n;
    if(position>queue->capacity){
        position = position - queue->capacity;
    }
    return queue->items[position];
}