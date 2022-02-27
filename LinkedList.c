#include "LinkedList.h"
typedef struct t_Node *Node;

struct t_Node
{
	element elem;
	struct t_Node* nextnode;

};


struct t_LinkedList
{
	copyFunction copyFunc;
	freeFunction freeFunc;
	iskeyFunction keyFunc;
	printFunction printFunc;
	equalFunction equalFunc;
	Node FirstNode;
	int size;
};

LinkedList createLinkedList(copyFunction copyf, freeFunction freef,iskeyFunction keyf, printFunction printfu,equalFunction equalf)
{
	LinkedList newlist = (LinkedList)malloc(sizeof(struct t_LinkedList));
	if (NULL==newlist)
	{
		return NULL;
	}
	newlist->copyFunc=copyf;
	newlist->freeFunc=freef;
	newlist->keyFunc=keyf;
	newlist->printFunc=printfu;
	newlist->equalFunc=equalf;
	newlist->FirstNode=NULL;
	newlist->size=0;
	return newlist;
}
void destroyList(LinkedList list){
	Node temp1= list->FirstNode;
	Node temp2;
	while(NULL!=temp1)
	{

		list->freeFunc(temp1->elem);
		temp2=temp1;
		temp1=temp1->nextnode;
		free(temp2);
	}
	free(list);
}
status appendNode(LinkedList list, element newelem)
{
	Node newnode = (Node)malloc(sizeof(struct t_Node));
	if (NULL==newnode)
	{
		return failure;
	}
	newnode->elem=newelem;
	newnode->nextnode=NULL;
	Node temp= list->FirstNode;
	if(NULL==temp)
	{
		list->FirstNode=newnode;
	}
	else
	{
		while(NULL!=temp->nextnode)
			{
				temp=temp->nextnode;
			}
		temp->nextnode=newnode;
	}
	list->size++;
	return success;
}
status deleteNode(LinkedList list, element delelem)
{
	Node temp= list->FirstNode;
	Node temp2;
	if(NULL==temp)
	{
		return failure;
	}
	else
	{
		while(NULL!=temp->nextnode)
		{
			if(list->equalFunc(delelem, temp->nextnode->elem)==0)
			{
				temp2=temp->nextnode;
				temp->nextnode=temp->nextnode->nextnode;
				list->freeFunc(temp2->elem);
				free(temp2);
				list->size--;
				return success;
			}
		}

	}
	return failure;
}
void displayList(LinkedList list)
{
	Node temp= list->FirstNode;
	while(NULL!=temp)
	{
		list->printFunc(temp->elem);
		temp=temp->nextnode;
	}

}

element searchByKeyInList(LinkedList list , element key)
{
	element ret;
	Node temp= list->FirstNode;
	while(NULL!=temp)
	{
		if(list->keyFunc(temp->elem,key)==true)
		{
			ret=temp->elem;
			return ret;
		}
		temp=temp->nextnode;
	}
	return NULL;
}

element searchByIndexInList(LinkedList list , int index)
{
	Node temp= list->FirstNode;
	if(index<list->size)
	{

		for (int i=0;i<index;i++)
		{
			temp=temp->nextnode;
		}
		return temp->elem;
	}
	return NULL;
}


