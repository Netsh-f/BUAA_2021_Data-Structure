#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define M_ARTICLE 20000
#define M_WORD 80
#define TRIE 2500050
#define KEY 100

char temp[M_WORD],word[M_WORD],ch,wcnt=0;
int p=0,i,j,k;
int trieh=1,acnt=0,sim=0;
int DN[KEY]={0};
double TF,IDF;

struct Trie
{
	int voc[26];
	int flag;//0无单词1启用2停用
	int k;
}trie[TRIE];

struct 	Web
{
	char ID[M_WORD];
	int id;
	int cnt,key[KEY];
}art[M_ARTICLE];

struct out
{
	double ans;
	int idnum;
}printout[M_ARTICLE];

int cmp(const void *p1, const void *p2);

int main(int argc, char *argv[])
{
	int sum=0,a=0;
	FILE *fp1 = fopen("dictionary.txt", "r");
	FILE *fp2 = fopen("stopwords.txt", "r");
	FILE *fp3 = fopen("article.txt", "r");
	FILE *fp4 = fopen("results.txt", "w");
	while(fscanf(fp1,"%s",temp)!=EOF)//建立trie 
	{
		for(i=0;i<(int)strlen(temp);i++)
		{
			a = temp[i]-'a';
			if(trie[p].voc[a]==0)
				trie[p].voc[a] = trieh++;
			p = trie[p].voc[a];
		}
		trie[p].flag = 1;
	}
	p=0;
	while(fscanf(fp2,"%s",temp)!=EOF)
	{
		for(i=0;i<(int)strlen(temp);i++)
		{
			a = temp[i]-'a';
			if(trie[p].voc[a]==0)
				break;
			p = trie[p].voc[a];
		}
		trie[p].flag = 2;
	}
	for(i=1;i<argc-1;i++)
	{
		p=0;
		for(j=0;j<strlen(argv);j++)
		{
			a = argv[j]-'a';
			if(trie[p].voc[a]==0)
				break;
			p = trie[p].voc[a];
		}
		if(trie[p].flag==1)
			trie[p].k = i;
	}
	while(fscanf(fp3,"%s",temp)!=EOF)
	{
		strcpy(art[acnt].ID,temp);
		while(ch = fgetc(fp3)&&feof(fp3))
		{
			if(ch=='\f')
				break;
			if((ch>='a'&&ch<='z')||(ch>='A'&&ch<="Z"))
			{
				if(ch<='Z')
					word[wcnt++] = ch-'A'+'a';
				else
					word[wcnt++] = ch;
			}
			else if(wcnt!=0)
			{
				word[wcnt]='\0';
				p=0;
				for(i=0;i<strlen(word);i++)
				{
					a = word[i]-'a';
					if(trie[p].voc[a]==0)
						break;
					p = trie[p].voc[a];
				}
				if(trie[p].flag==1)
					art[acnt].cnt++;
				if(trie[p].k>=1)
					art[acnt].key[trie[p].k]++;
				wcnt = 0;
			}
		}
		art[acnt].id = acnt+1;
		printout[acnt].idnum = acnt;
		acnt++;
	}
	for(i=1;i<argc-1;i++)
	{
		for(j=0;j<acnt;j++)
		{
			if(art[j].key[i]>=1)
				DN[i]++;
		}
	}
	for(i=0;argv[1][i]!='\0';i++)
		 sum = 10*sum + (argv[1][i]-'0');
	for(i=1;i<argc-1;i++)
	{
		if(DN[i]==0)
			IDF=0;
		else
			IDF=log10((double)acnt/DN[i]);
		for(j=0;j<acnt;j++)
		{
			TF = (double)art[j].key[i]/art[j].cnt*100;
			printout[j].ans+=TF*IDF;
		}
	}
	qsort(printout,acnt,sizeof(printout[0]),cmp);
	for(i=0;i<5;i++)
	{
		if(printout[i].ans<1e-6)
			break;
		printf("%.6f %d %s\n",printout[i].ans,printout[i].idnum+1,art[printout[i].idnum].ID);
	} 
	for(i=0;i<sum;i++)
	{
		if(printout[i].ans<1e-6)
			break;
		fprintf(fp4,"%.6f %d %s\n",printout[i].ans,printout[i].idnum+1,art[printout[i].idnum].ID);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	return 0;
}

int cmp(const void *p1, const void *p2)
{
	if(fabs(((struct out*)p1)->ans - ((struct out*)p2)->ans) < 1e-6)
		return ((struct out*)p1)->idnum - ((struct out*)p2)->idnum;
	else
	{
		if(((struct out*)p2)->ans - ((struct out*)p1)->ans > 0)
			return 1;
		else
			return -1;
	}
}
