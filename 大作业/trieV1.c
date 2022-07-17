#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct trie{
	int son[26];
	int num;
}a[1000005];

int t = 0;
char x[15];

void buildTrie(){
	int p = 0, l = strlen(x);
	for(int i=0;i<l;i++){
		if(a[p].son[x[i]-'a'] == 0){
			a[p].son[x[i]-'a'] = ++t;
		}
		p = a[p].son[x[i]-'a'];
	}
}

int main(){
	
} 
