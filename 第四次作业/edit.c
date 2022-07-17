#include<stdio.h>
#include<string.h>
char word[550];
int cnto = 0, next[550], cntw;

struct operation{
	int num;
	int pos;
	char str[550];
}ope[2005];

void insert(int posi, char stri[]){
	int lens, p = 0;
	lens = strlen(stri);
	for(int i=0;i<lens;i++){
		cntw++;
		word[cntw] = stri[i];
		next[cntw] = cntw + 1;
	}
	for(int i=0;i<posi;i++){
		p = next[p];
	}
	next[cntw] = next[p];
	next[p] = cntw - lens + 1;
}

void del(int posd, int numd, char strd[]){
	int p = 0, pn, cnt = 0;
	for(int i=0;i<posd;i++){
		p = next[p];
	}
	pn = next[p];
	for(int i=0;i<numd;i++){
		strd[cnt++] = word[pn];
		pn = next[pn];
		if(pn == -1){
			break;
		}
	}
	strd[cnt] = '\0';
	next[p] = pn;
}

void display(){
	int p = 0;
	while(1){
		p = next[p];
		if(p == -1){
			break;
		}
		printf("%c", word[p]);
	}
	printf("\n");
}

int main(){
	int n, numt = 1, post, strtn, lenw;
	char strt[550];
	gets(word+1);
	lenw = strlen(word+1);
	cntw = lenw;
	for(int i=0;i<lenw;i++){
		next[i] = i+1;
	}
	next[lenw] = -1;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%d %d %s", &ope[i].num, &ope[i].pos, ope[i].str);
	}
	cnto = n;
	while(numt != -1){
		scanf("%d", &numt);
		if(numt == 1){
			scanf("%d %s", &post, strt);
			insert(post, strt);
			ope[cnto].num = 1; ope[cnto].pos = post; strcpy(ope[cnto].str, strt);
			cnto++;
		}else if(numt == 2){
			scanf("%d %d", &post, &strtn);
			del(post, strtn, strt);
			ope[cnto].num = 2; ope[cnto].pos = post; strcpy(ope[cnto].str, strt);
			cnto++;
		}else if(numt == 3){
			if(ope[cnto-1].num == 1){
				del(ope[cnto-1].pos, strlen(ope[cnto-1].str), strt);
				cnto--;
			}else if(ope[cnto-1].num == 2){
				insert(ope[cnto-1].pos, ope[cnto-1].str);
				cnto--;
			}
		}
	}
	display();
	return 0;
}
