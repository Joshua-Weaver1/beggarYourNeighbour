#include "stack.h"

/**
 * Creates a stack with a given capacity.
 * @param stackItemCapacity: The maximum number of items the stack can hold.
 * @return: The stack.
*/
Stack* createStack(int stackItemCapacity){
    Stack* stack;
    stack = (Stack *)malloc(sizeof(Stack));

    stack->items = (int*)malloc(sizeof(int)*stackItemCapacity);
    stack->size = 0;
    stack->capacity = stackItemCapacity;
    stack->head=-1;

    return stack;
}

/**
 * Frees the memory allocated to the stack.
 * @param stack: The stack to free.
*/
void wipeStack(Stack* stack){
    free(stack->items);
}

/**
 * Removes the top item from the stack.
 * @param stack: The stack to pop from.
 * @return: The item that was popped.
*/
int popStack(Stack* stack){
    if(stack->size==0){
        printf("The stack has no items!\n");
        exit(-1);
    }
    else{
        int item = stack->items[stack->head];
        stack->size--;
        stack->head--;
        return item;
    }
}

/**
 * Adds an item to the top of the stack.
 * @param stack: The stack to push to.
 * @param item: The item to push.
*/
void pushStack(Stack *stack,int item){
    if(stack->size == stack->capacity){
        printf("The Stack is at capacity!\n");
    }
    else{
        stack->head++;
        stack->size++;
        stack->items[stack->head] = item;
    }
}

/**
 * Prints the contents of the stack.
 * @param stack: The stack to print.
*/
void showStack(Stack* stack){
    int i;
    for (i=0;i<stack->size;i++){
        printf(" %d ",stack->items[i]);
    }
}

/**
 * Gets the item at the top of the stack.
 * @param stack: The stack to get the item from.
 * @return: The item at the top of the stack.
*/
int getHeadOfStack(Stack* stack){
    if(stack->size==0){
        return -1;
    }

    return stack->items[stack->head];
}

/**
 * Gets the number of items in the stack.
 * @param stack: The stack to get the size of.
 * @return: The number of items in the stack.
*/
int getStackSize(Stack* stack){
    return stack->size;
}