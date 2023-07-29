#include <stdio.h>
#include <stdlib.h>

// Define the Queue struct with 5 fields: tail, head, items, capacity, and size.
typedef struct QueueStruct{
    int tail; // Index of the tail item in the queue.
    int head; // Index of the head item in the queue.
    int* items; // Pointer to the array of items.
    int capacity; // Maximum number of items that can be stored in the queue.
    int size; // Current number of items in the queue.
} Queue;

// Functions for the stack.
Queue* createQueue(int);
void removeFromQueue(Queue*);
int getFrontOfQueue(Queue*);
void addToQueue(Queue*,int);
void wipeQueue(Queue*);
int getQueueSize(Queue*);
int getSpecificItem(Queue*,int);
void printQueue(Queue*);