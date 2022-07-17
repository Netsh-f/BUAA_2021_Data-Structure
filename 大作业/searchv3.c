#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_ARTICLE 20000
#define MAX_WORD 80
#define MAX_TRIE 2500050
#define MAX_KEY 100

int articleNum, trieNum, simNum;
int idfkey[MAX_KEY];
int DN[MAX_KEY];

struct articleNode{
	char id[MAX_WORD];
	int idnum;
	int totalNum;
	int cntkey[MAX_KEY];
	double sim;
}article[MAX_ARTICLE], articleB[MAX_ARTICLE];

struct trieTree{
	int next[26];
	int stop;//0无单词1启用2停用
	int key;//存放编号，key路径赋值-1，查找时若为0则停止 
}trie[MAX_TRIE];

void insert(char s[]){
	int p = 0, lens = strlen(s);
	for(int i=0;i<lens;i++){
		if(trie[p].next[s[i]-'a'] == 0){
			trie[p].next[s[i]-'a'] = ++trieNum;
		}
		p = trie[p].next[s[i]-'a'];
	}
	trie[p].stop = 1;
}

void stopword(char s[]){
	int p = 0, lens = strlen(s);
	for(int i=0;i<lens;i++){
		if(trie[p].next[s[i]-'a'] == 0){
			return;
		}
		p = trie[p].next[s[i]-'a'];
	}
	trie[p].stop = 2;
}

void initkey(char s[], int x){//x为key编号1---
	int p = 0, lens = strlen(s);
	for(int i=0;i<lens;i++){
		if(trie[p].next[s[i]-'a'] == 0){
			return;
		}
		p = trie[p].next[s[i]-'a'];
	}
	if(trie[p].stop == 1){
		trie[p].key = x;
	}
}

void findkey(char s[], int x){//x为文章编号,当前articleNum 
	int p = 0, lens = strlen(s);
	for(int i=0;i<lens;i++){
		if(trie[p].next[s[i]-'a'] == 0){
			return;
		}
		p = trie[p].next[s[i]-'a'];
	}
	if(trie[p].stop == 1){
		article[x].totalNum++;
	}
	if(trie[p].key > 0){		
		article[x].cntkey[trie[p].key]++;	
	}
}

void sort(int n){
	double simMax;
	int k;
	struct articleNode t;
	for(int i=0;i<n;i++){
		simMax = 0;
		for(int j=i;j<articleNum;j++){
			if(article[j].sim > simMax){
				simMax = article[j].sim;
				k = j;
			}
		}
		t = article[i];
		article[i] = article[k];
		article[k] = t;
	}
}

int main(int argc, char *argv[]){
	FILE *fDictionary = fopen("dictionary.txt", "r");
	FILE *fStopwords = fopen("stopwords.txt", "r");
	FILE *fArticle = fopen("article.txt", "r");
	FILE *fResult = fopen("results.txt", "w");
	
	char buf[MAX_WORD], c, word[MAX_WORD];
	int cntw = 0;
	
	while(fscanf(fDictionary, "%s", buf) != EOF){
		insert(buf);
	}
	while(fscanf(fStopwords, "%s", buf) != EOF){
		stopword(buf);
	}
	for(int i=1;i<=argc-2;i++){
		initkey(argv[i+1], i);//key编号为i
	}
	while(fscanf(fArticle, "%s", buf) != EOF){
		strcpy(article[articleNum].id, buf);
		while((c = fgetc(fArticle)) != '\f' && !feof(fArticle)){
			if(c == '\f'){
				break;
			}
			if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
				word[cntw++] = (c >= 'A' && c <= 'Z')?(c - 'A' + 'a'):c;
			}else if(cntw > 0){
				word[cntw] = '\0';
				findkey(word, articleNum);
				cntw = 0;
			}
		}
		article[articleNum].idnum = articleNum + 1;
		articleNum++;
	}
	for(int i=1;i<=argc-2;i++){
		for(int j=0;j<articleNum;j++){
			if(article[j].cntkey[i] > 0){
				DN[i]++;
			}
		}
	}
	double IDF, TF;
	for(int i=1;i<=argc-2;i++){
		if(DN[i] == 0){
			IDF = 0;
		}else{
			IDF = log10((double)articleNum / DN[i]);
		}
		for(int j=0;j<articleNum;j++){
			TF = (double)article[j].cntkey[i]/article[j].totalNum*100;
			article[j].sim += TF * IDF;
		}
	}
	
	int num = 0;
	for(int i=0;argv[1][i]!='\0';i++){
		num = num * 10 + argv[1][i] - '0';
	}
	
	sort(num);
	
	for(int i=0;i<5;i++){
		if(article[i].sim < 1e-6)
			break;
		printf("%.6f %d %s\n", article[i].sim, article[i].idnum, article[i].id);
	}
	for(int i=0;i<num;i++){
		if(article[i].sim < 1e-6)
			break;
		fprintf(fResult, "%.6f %d %s\n", article[i].sim, article[i].idnum, article[i].id);
	}
	
	return 0;
}
