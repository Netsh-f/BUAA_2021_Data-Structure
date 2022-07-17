#include<stdio.h>
#include<stdlib.h>
typedef struct monkey
{
	int num;
	struct monkey* next;
}mk;
mk *head=NULL,*node,*end,*p; 
int main()
{
	int m,n,q;
	int i;
	scanf("%d %d %d",&n,&m,&q);
	head = (mk*)malloc(sizeof(mk));
	head->num=1; 
	end = head;
	for(i=2;i<=n;i++)
	{
		node = (mk*)malloc(sizeof(mk));
		node->num=i;
		end->next = node;
		end = node;
	}
	end->next=head;
	p=head;
	for(i=1;i<q;i++)
		p=p->next;
	while(p->next != p)
	{
		for(i=1;i<m-1;i++)
			p=p->next;
		node=p->next;
		p->next=p->next->next;
		p = p->next;
		free(node);
	}
	printf("%d",p->num);
	return 0;
} 
