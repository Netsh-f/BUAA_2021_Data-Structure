#include <stdio.h>
#include <string.h>
int main()
{
	FILE *fr,*fw;
	fr=fopen("books.txt","r");
	if(fr==NULL)
	return 1;
	char p[700][100],p1[700][50],p2[700][50],p3[700][20],c[2000],d[2000],a[2000],b[2000],s[2000],z;
	int i=0,j,k,m;
	while(fgets(s,2000,fr)!=NULL)
	{
		for(j=0;s[j]!=' ';j++)
		p[i][j]=s[j];
		p[i][j]='\0';
		for(j+=1,k=0;s[j]!=' ';j++,k++)
		p1[i][k]=s[j];
		p1[i][k]='\0';
		for(j+=1,k=0;s[j]!=' ';j++,k++)
		p2[i][k]=s[j];
		p2[i][k]='\0';
		for(j+=1,k=0;s[j]!='\n';j++,k++)
		p3[i][k]=s[j];
		p3[i][k]='\0';
		for(j=i-1;j>=0;j--)
		{
			m=strcmp(p[j+1],p[j]);
			if(m<0)
			{
				strcpy(a,p[j+1]);
				strcpy(b,p1[j+1]);
				strcpy(c,p2[j+1]);
				strcpy(d,p3[j+1]);
				strcpy(p[j+1],p[j]);
				strcpy(p1[j+1],p1[j]);
				strcpy(p2[j+1],p2[j]);
				strcpy(p3[j+1],p3[j]);
				strcpy(p[j],a);
				strcpy(p1[j],b);
				strcpy(p2[j],c);
				strcpy(p3[j],d);
			}
			else
			break;
		}
		i++;
	}
	fclose(fr);
	scanf("%c",&z);
	getchar();
	while(z!='0')
	{
		if(z=='1')
		{
			gets(s);
			for(j=0;s[j]!=' ';j++)
			p[i][j]=s[j];
			p[i][j]='\0';
			for(j+=1,k=0;s[j]!=' ';j++,k++)
			p1[i][k]=s[j];
			p1[i][k]='\0';
			for(j+=1,k=0;s[j]!=' ';j++,k++)
			p2[i][k]=s[j];
			p2[i][k]='\0';
			for(j+=1,k=0;s[j]!='\0';j++,k++)
			p3[i][k]=s[j];
			p3[i][k]='\0';
			for(j=i-1;j>=0;j--)
			{
				m=strcmp(p[j+1],p[j]);
				if(m<0)
				{
					strcpy(a,p[j+1]);
					strcpy(b,p1[j+1]);
					strcpy(c,p2[j+1]);
					strcpy(d,p3[j+1]);
					strcpy(p[j+1],p[j]);
					strcpy(p1[j+1],p1[j]);
					strcpy(p2[j+1],p2[j]);
					strcpy(p3[j+1],p3[j]);
					strcpy(p[j],a);
					strcpy(p1[j],b);
					strcpy(p2[j],c);
					strcpy(p3[j],d);
				}
				else
				break;
			}
			i++;
		}
		else if(z=='2')
		{
			gets(s);
			for(j=0;j<i;j++)
			if(strstr(p[j],s)!=NULL)
			printf("%-50s%-20s%-30s%-10s\n",p[j],p1[j],p2[j],p3[j]);
		}
		else
		{
			
			gets(s);
			for(j=0;j<i;j++)
			{
				if(strstr(p[j],s)!=NULL)
				{
				for(k=j+1;k<i;k++)
				{
					strcpy(p[k-1],p[k]);
					strcpy(p1[k-1],p1[k]);
					strcpy(p2[k-1],p2[k]);
					strcpy(p3[k-1],p3[k]);
				}
				i--;
				j--;
				}
			}
		}
		z=getchar();
		getchar();
	}
	fw=fopen("ordered.txt","w");
	if(fw==NULL)
	return 2;
	for(j=0;j<i;j++)
	fprintf(fw,"%-50s%-20s%-30s%-10s\n",p[j],p1[j],p2[j],p3[j]);
	return 0;
}
