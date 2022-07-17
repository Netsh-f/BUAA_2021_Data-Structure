#include<stdio.h>
#include<string.h>
int main()
{
	char s1[30],s2[30];
	int a[26]={0};
	int i=0,j=0,n;
	gets(s1);
	int len1=strlen(s1),len2;
	FILE *f1 = fopen("encrypt.txt","r");
	FILE *f2 = fopen("output.txt","w");
	char enc[100];
	for(i=0;i<len1;i++)
	{
		n=(int)(s1[i]-'a');
		a[n]+=1;
		if(a[n]==1)
		{
			s2[j]=s1[i];
			j++;		
		} 
	}
	s2[j] = '\0';//ฒน'\0' 
	len2=strlen(s2);
	j=len2;
	for(i=25;i>=0;i--)
	{
		if(a[i]==0)
		{
			s2[j]='a'+i;
			j++; 
		}
	}
	for(i=0;i<=25;i++)
		printf("%c",s2[i]);
	fgets(enc,100,f1);
	for(i=0;i<strlen(enc);i++)
	{
		if(enc[i]>='a'&&enc[i]<='z')
			fprintf(f2,"%c",s2[enc[i]-'a']);
		else
			fprintf(f2,"%c",enc[i]); 
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
