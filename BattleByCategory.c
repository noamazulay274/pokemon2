#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
struct battle_s
{
	int capacity;
	int numberOfCategories;
	LinkedList list;
	getCategoryFunction getCategoryFunc;
	getAttackFunction getAttackFunc;
	printFunction printElementFunc;
	freeFunction freeFunc;
	copyFunction copyFunc;
};

Battle createBattleByCategory(int cap,int numberOfCat,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{

	Battle newbattle= (Battle)malloc(sizeof(struct battle_s));
	newbattle->capacity=cap;
	newbattle->copyFunc=copyElement;
	newbattle->numberOfCategories=numberOfCat;
	newbattle->freeFunc=freeElement;
	newbattle->getAttackFunc=getAttack;
	newbattle->getCategoryFunc=getCategory;
	newbattle->printElementFunc=printElement;
	newbattle->list=createLinkedList(copyheap, destroyHeap, issamename, printHeap, heapgreaterthan);
	char *token = strtok(categories, ",");
	MaxHeap newheap;
	   /* walk through other tokens */
	   while( NULL!= token)
	   {
		  newheap =CreateHeap(copyElement, freeElement, printElement, equalElement, numberOfCat, token);
		  appendNode(newbattle->list, newheap);
	      token = strtok(NULL, ",");
	   }
	return newbattle;
}
status destroyBattleByCategory(Battle b)
{
	destroyList(b->list);
	free(b);
	return success;
}
status insertObject(Battle b, element elem)
{
	MaxHeap heap =(MaxHeap)searchByKeyInList(b->list, b->getCategoryFunc(elem));
	if (NULL==heap)
	{
		return failure;
	}
	return insertToHeap(heap, elem);

}

void displayObjectsByCategories(Battle b)
{
	displayList(b->list);
}


element removeMaxByCategory(Battle b,char* category)
{
	MaxHeap heap =searchByKeyInList(b->list, category);
		if (NULL==heap)
		{
			return NULL;
		}
		return PopMaxHeap(heap);
}


int getNumberOfObjectsInCategory(Battle b,char* category)
{
	MaxHeap heap =searchByKeyInList(b->list, category);
		if (NULL==heap)
		{
			return -1;
		}
		return getHeapCurrentSize(heap);
}
element fight(Battle b,element elem)
{
	MaxHeap heap= searchByIndexInList(b->list,0);
	element max=TopMaxHeap(heap);
	int first;
	int second;
	element compa;
	for(int i=0; i<b->numberOfCategories;i++)
	{
		heap= searchByIndexInList(b->list,i);
		compa =TopMaxHeap(heap);
		if (NULL== compa)
		{
			continue;
		}
		if(b->getAttackFunc(compa,elem,&first,&second)>b->getAttackFunc(max,elem,&first,&second))
		{
			b->freeFunc(max);
			max=b->copyFunc(compa);
		}
		b->freeFunc(compa);
	}
	if (NULL==max)
	{
		return NULL;
	}
	b->getAttackFunc(max,elem,&first,&second);
	printf("The final battle between:\n");
	b->printElementFunc(elem);
	printf("In this battle his attack is :%d\n\n",second);
	printf("against ");
	b->printElementFunc(max);
	printf("In this battle his attack is :%d\n\n",first);
	if(first==second)
	{
		b->freeFunc(max);
		printf("IT IS A DRAW.\n");
		return elem;
	}
	if(first>second)
		{
			printf("THE WINNER IS:\n");
			b->printElementFunc(max);
			return max;
		}
	printf("THE WINNER IS:\n");
	b->printElementFunc(elem);
	b->freeFunc(max);
	return elem;

}

