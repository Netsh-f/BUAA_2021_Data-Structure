#include<stdio.h>
#include<string.h>
struct bracket 
{
	char c;
	int line;
}stack[205],in[205];
int main()
{
	char word[205];
	char *p1,*p2,*p3,temp;
	int cnt1=0,num=0,len=0,flag=0;
	int i=0,j=0,k=0;
	FILE *f1 = fopen("example.c","r");
	while(fgets(word,200,f1)!=NULL)
	{
		cnt1++;
		p1 = strstr(word,"//");
		p2 = strstr(word,"/*");
		if(p1==NULL&&p2==NULL)
			len = strlen(word);
		else if(p1==NULL&&p2!=NULL)
			len = p2 - word;
		else if(p1!=NULL&&p2==NULL)
			len = p1 - word;
		else
		{
			if(p1>=p2)
				len = p2 - word;
			else
				len = p1 - word;
		}//确定长度，排除注释
		for(i=0;i<len;i++)
		{
			if(word[i]=='(')
			{
				stack[j].c = '(';
				stack[j].line = cnt1;
				in[k].c = '(';
				in[k].line = cnt1;
				j++;
				k++;
			}
			else if(word[i]==')')
			{
				in[k].c = ')';
				in[k].line = cnt1;
				k++;
				if(stack[j-1].c=='(')
					j--;
				else
				{
					temp=')';
					num=cnt1;
					flag=1;
					break;
				}
				
			}
			else if(word[i]=='{')
			{
				in[k].c = '{';
				in[k].line = cnt1;
				k++;
				if(stack[j-1].c=='(')
				{
					temp='(';
					num=stack[j-1].line;
					flag=1;
					break;
				}
				else
				{
					stack[j].c = '{';
					stack[j].line = cnt1;
					j++;
				}
			}
			else if(word[i]=='}')
			{
				in[k].c = '}';
				in[k].line = cnt1;
				k++;
				if(stack[j-1].c=='{')
					j--;
				else
				{
					temp='}';
					num=cnt1;
					flag=1;
					break;
				}
			}
			else if(word[i]=='\'')
			{
				p3 = strchr(word+i+1,'\'');
				if(p3!=NULL)
					i=p3-word;
				else
					continue;
			}
			else if(word[i]=='\"')
			{
				p3 = strchr(word+i+1,'\"');
				if(p3!=NULL)
					i=p3-word;
				else
					continue;
			}
		}
		if(flag==1)
		{
			printf("without maching '%c' at line %d",temp,num);
			break;
		}
	}
	if(flag==0)
	{
		if(j==0)
		{
			for(i=0;i<k;i++)
				printf("%c",in[i].c);
		}
		else
			printf("without maching '%c' at line %d",stack[j].c,stack[j].line-1);
	}
	return 0;
 } 
