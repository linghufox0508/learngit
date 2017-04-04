/*****************************************/
/*
 yinyapeng create this file for list learn 2016/05/16

*/

#include"stdio.h"
#include"malloc.h"
#include"stdlib.h"
struct list_head {
	struct list_head *next;
	struct list_head *pre;
};

typedef struct Node{
	int data;
	struct Node *pre;
	struct Node *next;
}NODE,*PNODE;

PNODE create_list();
PNODE traverse_list(PNODE);
int main(void)
{
	PNODE pHead = NULL;
	pHead = create_list();
	traverse_list(pHead);

	return 0;
}
PNODE traverse_list(PNODE pHead)
{
	while(NULL != pHead) {
		
		printf("the value is %d",pHead->data);
		pHead = pHead->next;

	}
}

PNODE create_list()
{
	PNODE pHead = NULL;
	PNODE pTail = NULL;

	int length;
	int i;
	int val;

        if((pHead = (PNODE)malloc(sizeof(NODE))== NULL){
	
		printf("allocate memory fail\n");
		exit(-1);
	}	
	pTail = pHead;
	pTail->next = NULL;

	printf("pleare input the length of list you want \n");
	scanf("%d",&length);
	for (i = 0; i < length;i++)
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew){
			printf("allocate memory fail\n");
			exit(-1);		
		}
		printf("please input the data \n");
		scanf("%d",&val);
		pNew->data = val;		
		pTail->next = pNew;
		pTail = pNew;		
	}
	return pHead;
}
