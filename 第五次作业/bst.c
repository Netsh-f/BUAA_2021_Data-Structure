#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *lc;
	struct node *rc;
}*root = NULL;

struct node *cre(int x){
	struct node *p;
	p = (struct node*)malloc(sizeof(struct node));
	p->data = x;
	p->lc = p->rc = NULL;
	return p;
};

void insert(int x, struct node *p){
	if(x < p->data){
		if(p->lc == NULL){
			p->lc = cre(x);
		}else{
			insert(x, p->lc);
		}
	}
	if(x >= p->data){
		if(p->rc == NULL){
			p->rc = cre(x);
		}else{
			insert(x, p->rc);
		}
	}
}

void display(struct node *p, int depth){
	if(p == NULL)
		return ;
	if(p->lc == NULL && p->rc == NULL){
		printf("%d %d\n", p->data, depth);
	}else{
		display(p->lc, depth+1);
		display(p->rc, depth+1);
	}
}

int main(){
	int n, t;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%d", &t);
		if(root == NULL)
			root = cre(t);
		else
			insert(t, root);
	}
	display(root, 1);
	return 0;
}
