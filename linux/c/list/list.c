#include"stdio.h"
#include"malloc.h"
#include"stdlib.h"

typedef struct Node{
	int data;
	struct Node *next;	
}NODE,*PNODE;

PNODE create_singlelist()
{
	PNODE phead = NULL;
	phead = (PNODE)malloc(sizeof(NODE));
	
	if (NULL != phead) {
		printf("create single list success\n");
	}
	phead->data = 0;
	phead->next = NULL;
	
	return phead;
	
}

void traverse_list(PNODE pNew)
{
	if (NULL == pNew){
		printf("error,list is empty\n");
	}

	while (pNew != NULL)
	{
		printf("%d",pNew->data);
	}
	printf("\n");
}
int main(void)
{	
	int num;
	int i,value;
	PNODE phead = create_singlelist();
	
	printf("please input the length of list\n");
	scanf("%d",&num);
	printf("please input the value\n");
	for(i = num; i< 1; i--)
	{
		scanf("%d",&value);
		
		ptail = (PNODE)malloc(sizeof(NODE));

		ptail->data = value;
		
	}	
//	traverse_list(pHead);
	free(phead);
	return 0;
}
