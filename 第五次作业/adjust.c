#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int num;
	int data;
	int cnt;
	struct node *ch[3];
}*root = NULL;

struct node *creNode(int x){
	struct node *p;
	p = (struct node*)malloc(sizeof(struct node));
	p->cnt = -1;
	p->num = x;
	for(int i=0;i<3;i++)
		p->ch[i] = NULL;
	return p;
}

struct node *search(struct node *p, int x){
	if(p == NULL){
		return NULL;
	}else if(x == p->num){
		return p;
	}else{
		search(p->ch[0], x);
		search(p->ch[1], x);
		search(p->ch[2], x);
	}
}

void build(struct node *p1, struct node *p2){
	
}

int main(){
	int n;
	while(1){
		scanf("%d", &n);
		if(n == -1)
			break;
		if(root == NULL)
			root = creNode(n);
		
	}
}
