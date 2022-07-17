#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
#define PI 3.14159265
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int inp[1024][1];
char ak[1024];
char az[1024];
char xx[1024];
typedef struct tt{
	char c;
	struct tt *next;
}*list,lst;

int main()
{
	FILE *pf1=fopen("in.txt","r");
	FILE *pf2=fopen("in_crpyt.txt","w");
	int i,j,num;
	list head=NULL,p=NULL,r=NULL;
	gets(ak);
	for(i=0;i<strlen(ak);i++)
	{
			inp[ak[i]][0]++;
	}
	for(i=0,j=0;i<strlen(ak);i++)
	{
		if(inp[ak[i]][0]>=1)
		{
			az[j]=ak[i];
			j++;
			inp[ak[i]][0]=-1;
		}
	}
	for(i=32;i<=126;i++)
	{
		if(inp[i][0]==0)
		{
			az[j]=i;
			j++;
		}
	}
	puts(az);
	for(i=0;i<j;i++)
	{
		r=(list)malloc(sizeof(lst));
		r->c=az[i];
		r->next=NULL;
		if(head==NULL)
		{
			head=p=r;
		}
		else
		{
			p->next=r; 
			p=p->next; 
		} 
	}
	p->next=head;
	num=head->c;
	while(p->next!=p)
	{
		xx[num]=p->next->c;
		r=p->next;
		p->next=r->next;
		num=r->c;
		free(r);
		for(i=1;i<num;i++)
		{
			r=p;
			p=p->next;
		}
	}
	//xx[p->c]=head->c;
	for(i=32;i<=126;i++)
	{
		printf("%c",i);
	}
	printf("\n");
	for(i=32;i<=126;i++)
	{
		printf("%c",xx[i]);
	}
	printf("\n%");
	memset(ak,0,strlen(ak)*sizeof(ak[0]));
	while(fgets(ak,1024,pf1)!=NULL)
	{
		for(i=0;i<strlen(ak);i++)
		{
			if(ak[i]>=32&&ak[i]<=126)
			ak[i]=xx[ak[i]];
		}
		fputs(ak,pf2);
		puts(ak);
		memset(ak,0,strlen(ak)*sizeof(ak[0]));
	}
	fclose(pf1);
	fclose(pf2);
	return 0;
}
