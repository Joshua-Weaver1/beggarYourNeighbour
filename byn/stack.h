#include <stdio.h>
#include <stdlib.h>

typedef struct StackStruct{
        int capacity;
        int head;
        int size;
        int* items;
}Stack;

int popStack(Stack*);
int getHeadOfStack(Stack*);
void pushStack(Stack*,int);
void wipeStack(Stack*);
int getStackSize(Stack*);
void showStack(Stack*);
Stack* createStack(int);