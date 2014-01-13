#include "memory.h"

/* Do not change !! */
#define MAX_MEM 4096

static char mem[MAX_MEM];


typedef struct FreeNode{
	FreeNode * next;
	short start;
	size_t size;
}head* = NULL;




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
	/*if(head == NULL && size < MAX_MEM)
	{
		result = mem;
		head = (FreeNode*) malloc(sizeof(FreeNode));
		head->next = NULL;
		head->start = size;
		head->size = MAX_MEM - size;
	}else if(head != NULL)
	{
		FreeNode * node = head;
		while(node != NULL && node->size < size)
		{
			node = node->next;
		}

		if(node != NULL) //found free space
		{
			result = mem[node->start];
			node->size = node->size - size;
			node->start = node->start + size;
			/*if(size < node->length)
			{

			}else{

			}*//*
		}
	}*/

	if(head == NULL && size < MAX_MEM)
	{
		result = mem;
		head = (FreeNode*) malloc(sizeof(FreeNode));
		head->next = NULL;
		head->start = 0;
		head->size = size;
	}else if(head != NULL){
		FreeNode * node = head;
		int pos = 0;
		while(node != NULL && node->size < size)
		{
			if((node->start - pos) > size)
			{
				result = mem[pos];
				//create new node and insert#
				FreeNode* newNode = (FreeNode*) malloc(sizeof(FreeNode));
				newNode->start = pos;
				newNode->size = size;
				FreeNode* tmp = head;
				while(tmp->next != node)
				{
					tmp = tmp->next;
				}
				tmp->next = newNode;
				newNode->next = node;
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
			if((MAX_MEM - (tmp->start + tmp->size)) > size - 1)
			{
				int pos = tmp->start+tmp->size+1;
				result = mem[pos];
				FreeNode* newNode = (FreeNode*) malloc(sizeof(FreeNode));
				newNode->start = pos;
				newNode->size = size;
				newNode->next = null;
				tmp->next = newNode;
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

		if(ptr = mem)
		{
			if(head->next == NULL)
			{
				head = NULL;
				free(node);
			}else{
				head = head->next;
				free(node);
			}
		}else{
			while((mem[node->next->start]) == ptr)
			{
				node = node->next;
			}
			FreeNode * tmp = node->next;
			FreeNode * next = node->next->next;
			free(tmp);
		}
	}
}
#endif