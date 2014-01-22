#include "memory.h"
#include <stdlib.h>
#include <stdbool.h>

/* Do not change !! */
#define MAX_MEM 4096

static char mem[MAX_MEM];


typedef struct FreeNode {
	struct FreeNode * next;
	short start;
	size_t size;
} FreeNode;
FreeNode* head = NULL;

typedef struct TreeNode {
	struct TreeNode * left;
	struct TreeNode * right;
	int start;
	size_t size;
	bool isFree;
} TreeNode;
TreeNode * treeHead = NULL; 



int getNextPowerOfTwo(int number) 
{
	int powerOfTwo = 1;
	while (number > powerOfTwo) {
		powerOfTwo*=2;
	}
	return powerOfTwo;
}

TreeNode * constructTreeNode(int start, size_t size)
{
	TreeNode * node = (TreeNode*) malloc(sizeof(TreeNode));
	node->start = start;
	node->size = size;
	node->left = NULL;
	node->right = NULL;
	node->isFree = true;
	return node;
}

bool hasChildren(TreeNode * node)
{
	if(node->left == NULL && node->right == NULL)
		return false;
	return true;
}

void subdivide(TreeNode * node)
{
	if(!hasChildren(node))
	{
		node->isFree = false;
		size_t newSize = (size_t) node->size / 2;
		node->left = constructTreeNode(node->start, newSize);
		node->right = constructTreeNode(node->start + (int)newSize, newSize);
	}
}


void unite(TreeNode* node) 
{
	if(hasChildren(node))
	{
		if (hasChildren(node->left))
			unite(node->left);
		if (hasChildren(node->right))
			unite(node->right);
		
		if(node->left->isFree && node->right->isFree)
		{
			printf("New room from %d to %d\n",node->left->start,node->left->start+(int)node->right->size+(int)node->right->size );
			free(node->left);
			free(node->right);
			node->left = NULL;
			node->right = NULL;
			node->isFree = true;
		}
	}
}


int findFreePos(TreeNode * node, size_t size)
{
	size_t desiredSize = (size_t) getNextPowerOfTwo((int)size);
	int result = -1;
	
	if(!(!hasChildren(node) && !node->isFree))
	{
		if(node->size > desiredSize)
		{
			//search children
			subdivide(node);
			if((result = findFreePos(node->left,size)) < 0)
				result = findFreePos(node->right,size);
		}else if(node->size == desiredSize && node->isFree){
			//return this nodes position
			result = node->start;
			node->isFree = false;
			printf("The block (%d Byte) has found its place between %d and %d\n",(int)size,result,result+(int)desiredSize);
		}
	}
	
	return result;
}


TreeNode* getParent(void * ptr, TreeNode * node)
{
	TreeNode * result = NULL;
	
	if(hasChildren(node))
	{
		if(ptr == &(mem[node->left->start]) && !hasChildren(node->left))
			result = node;
		else 
			result = getParent(ptr, node->left);
		
		if(result == NULL){ // no result yet, try other side
			if (ptr == &(mem[node->right->start]) && !hasChildren(node->right))
				result = node;
			else 
				result = getParent(ptr, node->right);
		}
		
	} 
	
	return result;
}



#ifdef BUDDY
void* bs_malloc(size_t size)
{

	if (treeHead == NULL)
		treeHead = constructTreeNode(0, (size_t)MAX_MEM);
	void * result = NULL;
	int pos = findFreePos(treeHead,size);

	if(pos >= 0)
		result = (void*) &(mem[pos]);
	
    	errno=ENOMEM;
    	return result;
}

void bs_free(void *ptr)
{
	if (ptr==NULL)
		return;
	TreeNode * parent = NULL;
	if (hasChildren(treeHead)){
		parent = getParent(ptr, treeHead);
		// ERROR
		if(parent==NULL)
		{
			printf("ERROR\n");
			return;
		}
		else 
		{
			if(ptr == &(mem[parent->left->start])) {
				parent->left->isFree = true;
			}
			else if(ptr == &(mem[parent->right->start])) {
				parent->right->isFree = true;
			}
		}
	} else {
		treeHead->isFree = true;
		return;
	}
	unite(treeHead);
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
