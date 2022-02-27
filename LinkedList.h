#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_LinkedList *LinkedList;



LinkedList createLinkedList(copyFunction , freeFunction ,iskeyFunction ,printFunction,equalFunction);
void destroyList(LinkedList);
status appendNode(LinkedList , element );
status deleteNode(LinkedList , element );
void displayList(LinkedList );
element searchByKeyInList(LinkedList list , element key);
element searchByIndexInList(LinkedList list , int index);

#endif
