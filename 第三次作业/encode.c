#include<stdio.h>
#include<string.h>
char buf[150], s[2005], secret[150];
int alpha[150], next[2005];

int main(){
	FILE *fin, *fout;
	int lenb, cnt = 0, p = 1, a, lens;
	char prea;
	fin = fopen("in.txt", "r");
	fout = fopen("in_crpyt.txt", "w");
	gets(buf);
	lenb = strlen(buf);
	for(int i = 0; i < lenb; i++){
		if(alpha[buf[i]] == 0){
			buf[cnt++] = buf[i];
			alpha[buf[i]] = 1;
		}
	}
	for(int i = 32; i <= 126; i++){
		if(alpha[i] == 0){
			buf[cnt++] = i;
		}
	}
	for(int i = 0; i < cnt-1; i++){
		next[i] = i+1;
	}
	next[cnt-1] = 1;
	a = buf[0];
	prea = a;
	for(int i = 0; i < cnt-1; i++){
		for(int j = 0; j < prea-2; j++){
			p = next[p];
		}		
		secret[prea] = buf[next[p]];
		prea = buf[next[p]];
		next[p] = next[next[p]];
		p = next[p];
	}
	secret[buf[p]] = a;
	while(fgets(s, 2000, fin) != NULL){
		lens = strlen(s);
		for(int i = 0; i < lens; i++){
			if(s[i] >= 32 && s[i] <= 126)
				s[i] = secret[s[i]];
		}
		fputs(s, fout);
		fputs("\n", fout);
	}
	fclose(fin); fclose(fout);
	return 0;
}
