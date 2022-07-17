#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000050

int trie[MAX][26];
int cnt[MAX];
int id;

void insert(char s[]){
	int p = 0, lens = strlen(s);
	for(int i=0;i<lens;i++){
		if(trie[p][s[i]-'a'] == 0){
			trie[p][s[i]-'a'] = ++id;
		}
		p = trie[p][s[i]-'a'];
	}
	cnt[p]++;
}

int find(char s[]){
	int p = 0, lens = strlen(s);
	for(int i=0;i<lens;i++){
		if(trie[p][s[i]-'a'] == 0)
			return 0;
		p = trie[p][s[i]-'a'];
	}
	return cnt[p];
}

int main(){
	
}
