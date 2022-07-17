#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct x{
	char a[200];
	int n;
}word[2005];

int cmp(const void *p1, const void *p2){
	struct x *p3 = (struct x*)p1;
	struct x *p4 = (struct x*)p2;
	return strcmp(p3->a, p4->a);
}

int main(){
	FILE *f;
	char c;
	int cnt = 0, flag = 0, len = 0, num = 0;
	f = fopen("article.txt", "r");
	while((c = fgetc(f)) != EOF){
		if((c>='a' && c<='z')||(c>='A' && c<='Z')){
			if(c>='A' && c<='Z'){
				c = c-'A'+'a';
			}
			word[cnt].a[len++] = c;
			flag = 1;
		}else{
			if(flag == 1){
				word[cnt].a[len] = '\0';
				flag = 0;
				len = 0;
				cnt++;
			}
		}
	}
	qsort(word, cnt, sizeof(word[0]), cmp);
	for(int i=0; i<cnt; i++){
		if(strcmp(word[num].a, word[i].a) == 0){
			word[num].n++;
		}else{
			word[++num] = word[i];
			word[num].n++;
		}
	}
	for(int i=0; i<=num; i++){
		printf("%s %d\n", word[i].a, word[i].n);
	}
	return 0;
}
