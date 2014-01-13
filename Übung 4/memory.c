#include "memory.h"
#include <stdlib.h>

/* Do not change !! */
#define MAX_MEM 4096

static char mem[MAX_MEM];


typedef struct FreeNode {
	struct FreeNode * next;
	short start;
	size_t size;
} FreeNode;
FreeNode* head = NULL;






#ifdef BUDDY
void *bs_malloc(size_t size)
{
   errno=ENOMEM;
   return NULL;
}

void bs_free(void *ptr)
{
}
#endif 




#ifdef FIRST
void *bs_malloc(size_t size)
{
	char* result = NULL;
	
	// Nothing in List and size is not to big
	if (head == NULL && size < MAX_MEM)
	{
		result = mem;
		head = (FreeNode*) malloc(sizeof(FreeNode));
		head->next = NULL;
		head->start = 0;
		head->size = size;
		printf("The block (%d Byte) has found its place between %d and %d\n",(int)size,0,(int)head->size-1);
	} 
	// Soemthing is in listpositionition
	else if (head != NULL) 
	{
		FreeNode * node = head;
		int position = 0;
		while(node != NULL /*&& node->size < size*/)
		{
			if((node->start - position) > size)
			{
				result = &(mem[position]);
				//create new node and insert#
				FreeNode* newNode = (FreeNode*) malloc(sizeof(FreeNode));
				newNode->start = position;
				newNode->size = size;
				FreeNode* tmp = head;
				while(tmp->next != node)
				{
					tmp = tmp->next;
				}
				tmp->next = newNode;
				newNode->next = node;	
				printf("The block (%d Byte) has found its place between %d and %d\n",(int)newNode->size, newNode->start,newNode->start+(int)newNode->size-1);
				break;
			}
			node = node->next;
		}
		if(node == NULL)//last block
		{
			FreeNode * tmp = head;
			while(tmp->next != NULL)
			{
				tmp = tmp->next;
			}
	//		printf("Last Block %d\n",(int)(MAX_MEM - (tmp->start + tmp->size)));
			if((MAX_MEM - (tmp->start + tmp->size-1)) > size )
			{
				int position = tmp->start+tmp->size;
				result = &(mem[position]);
				FreeNode* newNode = (FreeNode*) malloc(sizeof(FreeNode));
				newNode->start = position;
				newNode->size = size;
				newNode->next = NULL;
				tmp->next = newNode;
				printf("The block (%d Byte) has found its place between %d and %d\n",(int)newNode->size,newNode->start,newNode->start+(int)newNode->size-1);
			}
		}
	}

   errno=ENOMEM;
   return result;
}

void bs_free(void *ptr)
{
	if(ptr != NULL)
	{
		FreeNode * node = head;

		if(ptr == &(mem[head->start]))
		{
			printf("The block (%d Byte) between %d bis %d has been deleted!\n",(int)head->size,0,(int)head->size-1);
			if(head->next == NULL)
			{
				head = NULL;
				free(node);
			}else{
				head = head->next;
				free(node);
			}
		}else{
			while(&(mem[node->next->start]) == ptr+1)
			{
				node = node->next;
			}
			FreeNode * tmp = node->next;
			node->next = node->next->next;
			printf("The block (%d Byte) between %d bis %d has been deleted!\n", (int)tmp->size,tmp->start,tmp->start+(int)tmp->size-1);
			free(tmp);
		}
	}
}
#endif