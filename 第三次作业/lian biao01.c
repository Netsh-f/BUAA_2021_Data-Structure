#include<stdio.h>
#include<stdlib.h>
int cnt;

struct node{
	int data;
	struct node *next;
	struct node *prev;
} *ph, *tail;

struct node* create(){
	struct node *pnew;
	pnew = (struct node*)malloc(sizeof(struct node));
	pnew->next = NULL;
	pnew->prev = NULL;
	cnt++;
	return pnew;
}

struct node* insert(struct node *p, int x){
	if(p == NULL){
		tail = ph = create();
		p = ph;
		p->data = x;
		return p;
	}
	struct node *pnew;
	pnew = (struct node*)malloc(sizeof(struct node));
	if(p->next != NULL){
		p->next->prev = pnew;
	}
	pnew->next = p->next;
	p->next = pnew;
	pnew->prev = p;
	pnew->data = x;
	return pnew;
}

void show(struct node *p){
	while(p->next != NULL){
		printf("%d\n", p->data);
		p = p->next;
	}
}

struct node* search(struct node *p, int x){
	for(struct node *i = p; i != NULL; i = i->next){
		if(i->data == x){
			return i;
		}
	}
	return NULL;
}

void delete(struct node *p){
	if(p->next == NULL && p->prev == NULL){
		ph = tail = NULL;
		free(p);
	}else if(p->prev == NULL){
		p->next->prev = NULL;
		ph = p->next;
		free(p);
	}else if(p->next == NULL){
		p->prev->next = NULL;
		tail = p->prev;
		free(p);
	}else{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
	}
}

int main(){
	
	for(int i=0;i<10;i++){
		tail = insert(tail, i*2);
	}
	show(ph);
	struct node *a = search(ph, 14);
	printf("a = %d\n", a->data);
	delete(a);
	show(ph);
	return 0;
}
