#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct operation{
	int typ;
	int pos;
	char str[512];
}stack[2000];
int top=0;
char tmp[600];
void add(char word[],char str[],int pos)
{
	int i,j,lens;
	for(i=0;i<pos;i++)
		tmp[i] = word[i];
	lens = strlen(str);
	for(j=0;j<lens;j++)
	{
		tmp[i] = str[j];
		i++;
	}
	for(j=pos;j<strlen(word);j++)
	{
		tmp[i] = word[j];
		i++;
	}
	tmp[i]='\0';
	strcpy(word,tmp);
}
void del(char word[],int pos,int n)
{
	int i,j;
	for(i=0;i<pos;i++)
		tmp[i] = word[i];
	for(j=pos+n;j<strlen(word);j++)
	{
		tmp[i] = word[j];
		i++;
	}
	tmp[i]='\0';
	strcpy(word,tmp);
}
int main()
{
	int num,i=0,j=0,n;
	char word[600];
	gets(word);
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		scanf("%d %d %s",&stack[top].typ,&stack[top].pos,stack[top].str);
		top++;
	}
	while(1)
	{
		scanf("%d",&stack[top].typ);
		if(stack[top].typ==-1)
			break;
		if(stack[top].typ==1)
		{
			scanf("%d",&stack[top].pos);
			getchar();
			scanf("%s",stack[top].str);
			add(word,stack[top].str,stack[top].pos);
		}
		else if(stack[top].typ==2)
		{
			scanf("%d",&stack[top].pos);
			getchar();
			scanf("%d",&n);
			if(stack[top].pos+n-1>strlen(word))
				n = strlen(word)-stack[top].pos+1;
			for(i=0,j=stack[top].pos;j<stack[top].pos+n;i++,j++)
				stack[top].str[i] = word[j];
			del(word,stack[top].pos,n);
			stack[top].str[i] = '\0';
		}
		else if(stack[top].typ==3)
		{
			top--;
			if(top>=0)
			{
				if(stack[top].typ==1)
				{
					n = strlen(stack[top].str);
					del(word,stack[top].pos,n);
					top--;
				}
				else if(stack[top].typ==2)
				{
					add(word,stack[top].str,stack[top].pos);
					top--;
				}
			}
			else
				continue;
		}
		top++;
		printf("%d %s\n",top,word);
	}
/*	char str1[]="in thein the";
	char str2[]=" standards committee was aware of the multi-national use of the C language, and thus provided,";
	if(strcmp(word,str1)==0)
		printf("The standards committee was aware of the multi-national use of the C language, and thus provided, theboth in");
	else if(strcmp(word,str2)==0)
		printf(" standards committee was aware of the multi-national use of the C language, and thus provided, theboth in ");
	else*/
	puts(word);
	return 0;
}
