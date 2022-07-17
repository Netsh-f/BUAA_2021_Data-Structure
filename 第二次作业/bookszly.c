#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct library
{
	char title[100];
	char author[100];
	char print[100];
	char day[100];	
}in[600];
int cmp(const void*p1,const void*p2)
{
	struct library *a = (struct library *)p1;
	struct library *b = (struct library *)p2;
	return strcmp(a->title,b->title);
}
int main()
{
	int type=0,cnt=0;
	int i=0,num=0;
	char word[200],search[200];
	FILE *f1 = fopen("books.txt","r");
	FILE *f2 = fopen("ordered.txt","w");
	while(fgets(word,200,f1) != NULL)
	{
		sscanf(word,"%s%s%s%s",in[cnt].title,in[cnt].author,in[cnt].print,in[cnt].day);
		cnt++;
	}
	qsort(in,cnt,sizeof(in[0]),cmp);
	while(scanf("%d",&type)!=EOF)
	{
		if(type==1)
		{
			scanf("%s%s%s%s",in[cnt].title,in[cnt].author,in[cnt].print,in[cnt].day);
			cnt++;
			qsort(in,cnt,sizeof(in[0]),cmp);
		}
		else if(type==2)
		{
			scanf("%s",search);
			for(i=0;i<cnt;i++)
			{
				if(strstr(in[i].title,search) != NULL)
					printf("%-50s%-20s%-30s%-10s\n",in[i].title,in[i].author,in[i].print,in[i].day);
			} 
		}
		else if(type==3)
		{
			scanf("%s",search);
			for(i=0;i<cnt;i++)
			{
				if(strstr(in[i].title,search) != NULL)
				{
					memset(in[i].title,'z'+1,sizeof(in[i].title));
					num+=1;
				}
			}
			qsort(in,cnt,sizeof(in[0]),cmp);
			cnt-=num;
			num=0;
		}
		else if(type==4){
			for(int i=0; i<cnt; i++){
				printf("%-50s%-20s%-30s%-10s\n",in[i].title,in[i].author,in[i].print,in[i].day);
			}
		}
		else if(type==0)
			break;
	} 
	for(i=0;i<cnt;i++)
		fprintf(f2,"%-50s%-20s%-30s%-10s\n",in[i].title,in[i].author,in[i].print,in[i].day);
	fclose(f1);
	fclose(f2);
	return 0;
} 
