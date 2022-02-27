#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_MaxHeap *MaxHeap;

MaxHeap CreateHeap(copyFunction , freeFunction ,printFunction,equalFunction,int,char*);
void destroyHeap(MaxHeap);
status insertToHeap(MaxHeap,element);
void printHeap(MaxHeap);
element PopMaxHeap(MaxHeap);
element TopMaxHeap(MaxHeap);
char* getHeapId(MaxHeap);
int getHeapCurrentSize(MaxHeap);
MaxHeap copyheap(MaxHeap);
bool issamename(MaxHeap,char*);
int heapgreaterthan (MaxHeap, MaxHeap);

#endif
