#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cnt, max, path[100], flag;

struct node{
	int data;
	int cnt;
	struct node *lc;
	struct node *rc;
}*root = NULL;

struct node *cre(int x){
	struct node *p;
	p = (struct node*)malloc(sizeof(struct node));
	p->data = x;
	p->cnt = 0;
	p->lc = p->rc = NULL;
	return p;
}

void insert(struct node *p, int x){
	cnt++;
	if(x < p->data){
		if(p->lc == NULL){
			p->lc = cre(x);
			p->lc->cnt++;
			if(p->lc->cnt > max)
				max = p->lc->cnt;
		}else{
			insert(p->lc, x);
		}
	}else if(x > p->data){
		if(p->rc == NULL){
			p->rc = cre(x);
			p->rc->cnt++;
			if(p->rc->cnt > max)
				max = p->rc->cnt;
		}else{
			insert(p->rc, x);
		}
	}else{
		p->cnt++;
		if(p->cnt > max)
			max = p->cnt;
	}
}

void DFS(struct node *p, int depth){
	if(p == NULL){
		return;
	}else{
		path[depth] = p->data;
		DFS(p->lc, depth+1);
		DFS(p->rc, depth+1);
		if(p->cnt == max && flag == 0){
			flag = 1;
			for(int i=0;i<=depth;i++){
				printf("%d ", path[i]);
			}
		}
	}
}

int main(){
	int n, x;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%d", &x);
		if(root == NULL)
			root = cre(x);
		else
			insert(root, x);
	}
	printf("%d\n", cnt);
	DFS(root, 0);
	return 0;
}
