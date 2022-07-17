#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	char s[105];
	int num;
	struct node *lc;
	struct node *rc;
}*root = NULL;

struct node *cre(char *s){
	struct node *p;
	p = (struct node*)malloc(sizeof(struct node));
	strcpy(p->s, s);
	p->lc = p->rc = NULL;
	p->num = 1;
	return p;
};

void insert(char *s, struct node *p){
	if(strcmp(s, p->s) > 0){
		if(p->rc == NULL){
			p->rc = cre(s);
		}else{
			insert(s, p->rc);
		}
	}else if(strcmp(s, p->s) == 0){
		p->num++;
	}else{
		if(p->lc == NULL){
			p->lc = cre(s);
		}else{
			insert(s, p->lc);
		}
	}
}

void display(struct node *p, int depth){
	if(p->lc != NULL)
		display(p->lc, depth+1);
	printf("%s %d\n", p->s, p->num);
	if(p->rc != NULL)
		display(p->rc, depth+1);
}

int main(){
	FILE *f = fopen("article.txt", "r");
	char str[5005], word[105];
	int lens, cnt = 0;
	while(fgets(str, 5005, f) != NULL){
		lens = strlen(str);
		for(int i=0;i<lens;i++){
			if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
				word[cnt++] = (str[i]>='A' && str[i]<='Z')?str[i]-'A'+'a':str[i];
			}else{
				if(cnt){
					word[cnt] = '\0';
					cnt = 0;
					if(root == NULL)
						root = cre(word);
					else
						insert(word, root);
				}
			}
		}
	}
	printf("%s", root->s);
	if(root->rc != NULL){
		printf(" %s", root->rc->s);
	}
	if(root->rc->rc != NULL){
		printf(" %s", root->rc->rc->s);
	}
	printf("\n");
	display(root, 1);
	return 0;
}
