#include <stdio.h>
#include "stack.c"
#include "queue.c"
#include "../shuffling/riffle.c"

int beggar(int,int*,int);
int finished(Queue**,int);
void gameOutput(Queue**,Stack*,int,int,int,int);
int* take_turn(Queue*, Stack*);
int checkQueueSize(Queue*);