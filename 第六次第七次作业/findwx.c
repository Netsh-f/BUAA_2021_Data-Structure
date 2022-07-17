#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
#define MAXSIZE 1024

#define NHASH  3001
#define MULT  37
unsigned int hash(char *str)
{
       unsigned int h=0;
       char *p;
       for(p=str; *p!='\0'; p++)
              h = MULT*h + *p;
       return h % NHASH;
}
char xx[20];
char str[3501][20];
int mid_find(char xx[],int let,int rit)
{
	int mid;
	int time=0;
	while(let<=rit)
	{
		mid=(let+rit)/2;
		time++;
		if(strcmp(str[mid],xx)==0)
		{
			printf("1 %d\n",time);
			return 1;
		}
		else if(strcmp(str[mid],xx)>0)
		rit=mid-1;
		else if(strcmp(str[mid],xx)<0)
		let=mid+1;
	}
	printf("0 %d\n",time);
	return 0;
}
typedef struct liad{
	char cc;
	int let;
	int rit;
}xs;
xs words[26];

typedef struct wkk{
	char hh[20];
	struct wkk *next;
}*xl,xline;
xl line[NHASH];

xl insert(xl head,char s[])
{
	xl p,q,r;
	r=(xl)malloc(sizeof(xline));
	strcpy(r->hh,s);
	r->next=NULL;
	for(p=head;p!=NULL&&strcmp(s,p->hh)>0;p=p->next)
		q=p;
	if(p==head)
	{
		r->next=head;
		return r;
	}
	else
	{
		q->next=r;
		r->next=p;
	}
	return head;
}
xl search(xl head,char s[])
{
	xl r;
	int tk=1;
	r=(xl)malloc(sizeof(xline));
	for(r=head;r->next!=NULL&&strcmp(r->hh,s)<0;r=r->next)
		tk++;
	if(strcmp(s,r->hh)==0)
	printf("1 %d\n",tk);
	else
	printf("0 %d\n",tk);
	return 0;
}
int main() 
{
	FILE *op=fopen("dictionary3000.txt","r");
	int step,count=0,times=0,m=0;
	while(1) //count=下标+2=数量+1 
	{
		if(fgets(str[count++],40,op)!=NULL)
		str[count-1][strlen(str[count-1])-1]='\0';
		else
		break;
	}
	scanf("%s%d",xx,&step);
//	puts(str[3314]);
	if(step==1)
	{
		for(int i=0; i<count-1; i++) 
		{
			times++;
			if(strcmp(str[i],xx)==0) 
			{
				printf("1 %d\n",times);
				break;
			}
			if(strcmp(str[i],xx)>0) 
			{
				printf("0 %d\n",times);
				break;
			}
			if(i==count-1)
			printf("0 %d\n",times);
		}
	}
	if(step==2)
	{
		mid_find(xx,0,count-2);
	}
	if(step==3)
	{
		for(int i=0;i<26;i++)
			words[i].cc='a'+i;
		words[0].let=0;
		for(int i=0;i<count-1;i++)
		{
			if(str[i+1][0]-str[i][0]!=0)
			{
				words[str[i][0]-'a'].rit=i;
				words[str[i+1][0]-'a'].let=i+1;
			}
		}
		mid_find(xx,words[xx[0]-'a'].let,words[xx[0]-'a'].rit);
	}
	if(step==4)
	{
		for(int i=0;i<NHASH;i++)
		line[i]=NULL;
		for(int i=0;i<count-1;i++)
		{
			int ak=hash(str[i]);
			line[ak]=insert(line[ak],str[i]);
		}
		search(line[hash(xx)],xx);
	}
	fclose(op);
	return 0;
}
