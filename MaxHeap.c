#include "MaxHeap.h"

struct t_MaxHeap
{
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction equalFunc;
	element * elemarray;
	int maxsize;
	int currentsize;
	char* name;
};


MaxHeap copyheap(MaxHeap heap)
{
	MaxHeap newheap=(MaxHeap)malloc(sizeof(struct t_MaxHeap));
	if (NULL==newheap)
	{
		return NULL;
	}
	newheap->copyFunc=heap->copyFunc;
	newheap->equalFunc=heap->equalFunc;
	newheap->freeFunc=heap->freeFunc;
	newheap->printFunc=heap->printFunc;
	newheap->maxsize=heap->maxsize;
	newheap->currentsize=heap->currentsize;
	newheap->elemarray=malloc((heap->currentsize)*sizeof(element));
	newheap->name=(char*)malloc(strlen(heap->name)+1);
	if (NULL==newheap->name)
	{
		return NULL;
	}
	strcpy(newheap->name,heap->name);
	for(int i=0;i<heap->currentsize;i++)
	{
		newheap->elemarray[i]= newheap->copyFunc(heap->elemarray[i]);
	}
	return newheap;
}





void MaxHeapify(MaxHeap heap, int i)
{
	int l = 2*i+1;
	int r = 2*(i+1);
	int largest=i;
	if(l<heap->currentsize && heap->equalFunc(heap->elemarray[l],heap->elemarray[i])==1)
	{
		largest=l;
	}
	if(r<heap->currentsize && heap->equalFunc(heap->elemarray[r],heap->elemarray[largest])==1)
	{
		largest=r;
	}
	if (largest!= i)
	{
		element temp = heap->elemarray[i];
		heap->elemarray[i]=heap->elemarray[largest];
		heap->elemarray[largest]=temp;
		MaxHeapify(heap,largest);
	}

}









MaxHeap CreateHeap(copyFunction copyf, freeFunction freef, printFunction printfu,equalFunction equalf,int max,char* newname)
{
	if (max<0)
	{
		return NULL;
	}
	MaxHeap newheap=(MaxHeap)malloc(sizeof(struct t_MaxHeap));
	if (NULL==newheap)
	{
		return NULL;
	}
	newheap->copyFunc=copyf;
	newheap->freeFunc=freef;
	newheap->printFunc=printfu;
	newheap->equalFunc=equalf;
	newheap->maxsize=max;
	newheap->elemarray=NULL;
	newheap->name=(char*)malloc(strlen(newname)+1);
	if (NULL==newheap->name)
	{
		return NULL;
	}
	strcpy(newheap->name,newname);
	newheap->currentsize=0;
	return newheap;
}

void destroyHeap(MaxHeap desheap)
{
	free(desheap->name);
	desheap->name=NULL;
	for (int i=0 ;i<desheap->currentsize;i++)
	{
		desheap->freeFunc(desheap->elemarray[i]);
	}
	free(desheap->elemarray);
	free(desheap);
}

status insertToHeap(MaxHeap heap,element elem)
{
	if(heap->maxsize==heap->currentsize)
	{
		return failure;
	}
	heap->currentsize++;
	heap->elemarray=realloc(heap->elemarray,heap->currentsize*sizeof(element));
	if(NULL==heap->elemarray)
	{
		return failure;
	}
	heap->elemarray[heap->currentsize-1]=elem;
	int i = heap->currentsize-1;
	int parent= (i-1)/2;
	while (i>0 && heap->equalFunc(heap->elemarray[i],heap->elemarray[parent])==1)
	{
		element temp = heap->elemarray[i];
		heap->elemarray[i]=heap->elemarray[parent];
		heap->elemarray[parent]=temp;
		i=parent;
		parent= (i-1)/2;
	}
	return success;
}


void printHeap(MaxHeap heap)
{
	MaxHeap printheap = copyheap(heap);
	if (NULL==printheap)
	{
		return ;
	}
	int size=printheap->currentsize;
	printf("%s:\n",printheap->name);
	if (size==0)
	{
		printf("No elements.\n\n");
	}
	for (int i=0;i<size;i++)
	{
	printf("%d. ",i+1);
	element el=PopMaxHeap(printheap);
	printheap->printFunc(el);
	printheap->freeFunc(el);
	}
	destroyHeap(printheap);
}

element PopMaxHeap(MaxHeap heap)
{
	if (heap->currentsize==0)
	{
		return NULL;
	}
	element elem= heap->copyFunc(heap->elemarray[0]);
	heap->freeFunc(heap->elemarray[0]);
	heap->elemarray[0]=heap->elemarray[heap->currentsize-1];
	heap->currentsize--;
	heap->elemarray=realloc(heap->elemarray,heap->currentsize*sizeof(element));
	if(heap->currentsize!=0 && NULL==heap->elemarray)
	{
		return NULL;
	}
	MaxHeapify(heap, 0);
	return elem;
}
element TopMaxHeap(MaxHeap heap)
{
	if (heap->currentsize==0)
	{
		return NULL;
	}
	element elem= heap->copyFunc(heap->elemarray[0]);
	return elem;
}

char* getHeapId(MaxHeap heap)
{
	char* nameret=(char*)malloc(sizeof(heap->name)+1);
	strcpy(nameret,heap->name);
	return nameret;
}
int getHeapCurrentSize(MaxHeap heap)
{
	return heap->currentsize;
}

bool issamename(MaxHeap heap,char* cmpname)
{
	if (NULL==heap)
	{
		return false;
	}
	if(strcmp(cmpname,heap->name)==0)
	{
		return true;
	}
	return false;
}



int heapgreaterthan (MaxHeap heap1, MaxHeap heap2)
{
	return(heap1->equalFunc(TopMaxHeap(heap1),TopMaxHeap(heap2)));
}
