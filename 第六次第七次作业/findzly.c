#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NHASH  3001
#define MULT  37
char dictionary[10000][25];
char search[25];
int dlen=0,cnt=0,i=0;
struct Index
{
	char c;
	int start,end;
}list[30];

typedef struct Hash
{
	char letter[25];
	struct Hash *next;
}*phash;
phash hashlist[10000];
int order()
{
	for(i=0;i<dlen;i++)
	{
		cnt++;
		if(strcmp(dictionary[i],search)==0)
			return 1;
		if(strcmp(dictionary[i],search)>0)
			return 0;
	}
	return 0;
}
int binary(int low,int high)
{
	int mid;
	while(low<=high)
	{
		cnt++;
		mid=(low+high)/2;
		if(strcmp(dictionary[mid],search)==0)
			return 1;
		else if(strcmp(dictionary[mid],search)<0)
			low=mid+1;
		else if(strcmp(dictionary[mid],search)>0)
			high=mid-1;
	}
	return 0;
}
int indexs()
{
	for(i=0;i<30;i++)
	{
		list[i].start=0;
		list[i].end=0;
	}
	char temp='a';
	list[0].c='a';
	for(i=0;i<dlen;i++)
	{
		if(dictionary[i][0]!=temp)
		{
			list[temp-'a'].end = i-1;
			temp = dictionary[i][0];
			list[temp-'a'].c = temp;
			list[temp-'a'].start = i;
		}
	}
	list[temp-'a'].end = dlen-1;
	int n = search[0]-'a';
	return binary(list[n].start,list[n].end);
}

unsigned int hash(char *str)
{
       unsigned int h=0;
       char *p;
       for(p=str; *p!='\0'; p++)
              h = MULT*h + *p;
       return h % NHASH;
}
phash create(char a[])//创建新指针 
{
	phash node=(phash)malloc(sizeof(struct Hash));
	node->next = NULL;
	strcpy(node->letter,a);
	return node;
}
void insert(char a[])
{
	int k = hash(a);
	phash tmp = hashlist[k];
	if(tmp==NULL)//没发生过碰撞 
	{
		tmp = create(a);
		hashlist[k] = tmp;
	}
	else
	{
		while(tmp->next!=NULL)
			tmp = tmp->next;
		tmp->next = create(a);
	}
}

int hashsearch()
{
//	for(i=0;i<10000;i++)
//		hashlist[i]=NULL;
	int k = hash(search);
	phash tmp = hashlist[k];
	if(tmp==NULL)
		return 0;
	else
	{
		while(tmp!=NULL)
		{
			cnt++;
			if(strcmp(tmp->letter,search)==0)
				return 1;
			else if(strcmp(tmp->letter,search) < 0)
				tmp = tmp->next;
			else
				return 0;
		}
	}
	return 0;
}
int main()
{
	int fway,fresult;
	FILE *in = fopen("dictionary3000.txt","r");
	i=0;
	while(fscanf(in,"%s",dictionary[i])!=EOF){
		insert(dictionary[i]);
		i++;
	}
	dlen = i-1;
	while(scanf("%s %d",search,&fway)!=EOF)
	{
		cnt=0;
		if(fway==1)
			fresult = order();
		else if(fway==2)
			fresult = binary(0,dlen);
		else if(fway==3)
			fresult = indexs();
		else if(fway==4)
			fresult = hashsearch();
		printf("%d %d\n",fresult,cnt);
		memset(search,'\0',sizeof(search));
	}
	printf("\n--%s--\n", hashlist[hash("yes")]->letter);
	fclose(in);
	return 0;
}
