#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_ARTICLE 20000
#define MAX_WORD 80
#define MAX_TRIE 2500050
#define MAX_KEY 100

int articleNum, trieNum, simNum;
int DN[MAX_KEY];

struct articleNode{
	char id[MAX_WORD];
	int idnum;
	int totalNum;
	int cntkey[MAX_KEY];
}article[MAX_ARTICLE], articleB[MAX_ARTICLE];

struct Ans{
	double sim;
	int index;
}ans[MAX_ARTICLE];

struct trieTree{
	int next[26];
	int stop;//0无单词1启用2停用
	int key;//存放key编号
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

int cmp(const void *p1, const void *p2){
	if(fabs(((struct Ans*)p1)->sim - ((struct Ans*)p2)->sim) < 1e-6)
		return ((struct Ans*)p1)->index - ((struct Ans*)p2)->index;
	else
		return ((struct Ans*)p2)->sim - ((struct Ans*)p1)->sim > 0 ? 1 : -1;
}

int main(int argc, char *argv[]){
	FILE *fDictionary = fopen("dictionary.txt", "r");
	FILE *fStopwords = fopen("stopwords.txt", "r");
	FILE *fArticle = fopen("article.txt", "r");
	FILE *fResults = fopen("results.txt", "w");
	
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
		ans[articleNum].index = articleNum;
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
			ans[j].sim += TF * IDF;
		}
	}
	
	int num = 0;
	for(int i=0;argv[1][i]!='\0';i++){
		num = num * 10 + argv[1][i] - '0';
	}
	
	qsort(ans, articleNum, sizeof(ans[0]), cmp);
	
	for(int i=0;i<5;i++){
		if(ans[i].sim < 1e-6)
			break;
		printf("%.6f %d %s\n", ans[i].sim, ans[i].index+1, article[ans[i].index].id);
	}
	for(int i=0;i<num;i++){
		if(ans[i].sim < 1e-6)
			break;
		fprintf(fResults, "%.6f %d %s\n", ans[i].sim, ans[i].index+1, article[ans[i].index].id);
	}
	
	return 0;
}
