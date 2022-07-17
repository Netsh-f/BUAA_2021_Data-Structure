#include<stdio.h>
#include<string.h>
char change(char a)
{
	if(a>='A'&&a<='Z')
		a+=32;
	return a;
}
int main()
{
	char in[100],out[100],word[1000];
	int n,m,l,flag=0;
	int i,j,k;
	char c;
	gets(in);
	gets(out);
	m = strlen(in);
	n = strlen(out);
	FILE *f1=fopen("filein.txt","r");
	FILE *f2=fopen("fileout.txt","w");
	i=0;
	while((c=fgetc(f1)) != EOF)//in->f1
	{
		word[i]=c;
		i++;
	}
	l=strlen(word);
	for(i=0;i<l;i++)
	{
		flag=0;
		if(change(word[i])==change(in[0]))
		{
			for(j=1;j<m;j++)
			{
				if(change(word[i+j])!=change(in[j]))
					flag=1;		
			}
			if(flag==0)
			{
				for(k=0;k<n;k++)
					fputc(out[k],f2);
				i=i+m-1;
			}
			else
				fputc(word[i],f2);
		} 
		else
			fputc(word[i],f2);
	}
	fclose(f1);
	fclose(f2);
	return 0;
 } 
