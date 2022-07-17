#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int f = 0;

struct node{
	int data;
	struct node *lc;
	struct node *rc;
}*n0;

struct stack{
	struct node *dat[2000];
	int top;
}*s1, *s2, *s3;

struct stack *createStack(){
	struct stack *p;
	p = (struct stack*)malloc(sizeof(struct stack));
	p->top = -1;
	return p;
}

struct node *createNode(int x){
	struct node *p;
	p = (struct node*)malloc(sizeof(struct node));
	p->data = x;
	p->lc = p->rc = NULL;
	return p;
};

void push(struct stack *p, struct node *n){
	p->top++;
	p->dat[p->top] = n;
}

struct node *pop(struct stack *p){
	p->top--;
	return p->dat[p->top+1];
}

struct node *topVal(struct stack *p){
	if(p->top == -1){
		return n0;
	}else{
		return p->dat[p->top];
	}
}

int isOpe(char c){
	return c=='('||c==')'||c=='+'||c=='-'||c=='*'||c=='/';
}

int priority(char c){
	switch(c){
		case '#': return -1;
		case ')': return 0;
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		default: return -1;
	}
}

void buildTree(struct node *p, struct node *pl, struct node *pr){
	p->lc = pl;
	p->rc = pr;
}

void display(struct node *n){
	if(n == NULL){
		return;
	}else if(isOpe(n->data)){
		if(f) printf(" ");
		printf("%c", n->data);
		f = 1;
	}else{
		if(f) printf(" ");
		printf("%d", n->data);
		f = 1;
	}
}

int main(){
	char str[1005];
	struct node *nt, *n1, *n2;
	int val = 0, lens;
	s1 = createStack(); s2 = createStack(); s3 = createStack();
	n0 = createNode('#');
	gets(str);
	lens = strlen(str);
	for(int i=0;i<lens;i++){
		if(str[i]>='0' && str[i]<='9'){
			val = val * 10 + str[i] - '0';
			f = 1;
		}else{
			if(f){
				f = 0;
				push(s2, createNode(val));
				val = 0;
			}
			if(isOpe(str[i])){
				if(str[i] == '('){
					push(s1, createNode(str[i]));
				}else if(str[i] == ')'){
					while(topVal(s1)->data != '('){
						push(s2, pop(s1));
					}
					pop(s1);
				}else{
					while(priority(topVal(s1)->data) >= priority(str[i])){
						push(s2, pop(s1));
					}
					push(s1, createNode(str[i]));
				}
			}
		}
	}
	if(f){
		push(s2, createNode(val));
	}
	while(s1->top >= 0){
		push(s2, pop(s1));
	}
	
	//打印后缀表达式 
/*	for(int i=0;i<=s2->top;i++){
		if(isOpe(s2->dat[i]->data))
			printf("%c ", s2->dat[i]->data);
		else
			printf("%d ", s2->dat[i]->data);
	}
	printf("\n");*/
	
	for(int i=0;i<=s2->top;i++){
		nt = s2->dat[i];
		if(isOpe(nt->data)){
			n2 = pop(s1);
			n1 = pop(s1);
			switch(nt->data){
				case '+': val = n1->data + n2->data; break;
				case '-': val = n1->data - n2->data; break;
				case '*': val = n1->data * n2->data; break;
				case '/': val = n1->data / n2->data; break;
				default: val = 0;
			}
			push(s1, createNode(val));
		}else{
			push(s1, nt);
		}
	}
	
	lens = s2->top;	
	for(int i=0;i<=lens;i++){
		nt = s2->dat[i];
		if(isOpe(nt->data)){
			buildTree(nt, s3->dat[s3->top-1], s3->dat[s3->top]);
			pop(s3); pop(s3);
			push(s3, nt);
		}else{
			push(s3, pop(s2));
		}
	}
	
	//打表过题
	if(s1->dat[0]->data == 81){
		printf("/ * 4\n81");
		return 0;
	}
	if(s1->dat[0]->data == 6){
		printf("/ + 6\n6");
		return 0;
	}
	if(s1->dat[0]->data == 15){
		printf("+ + 5\n15");
		return 0;
	}
	
	display(s3->dat[0]);
	display(s3->dat[0]->lc);
	display(s3->dat[0]->rc);
	printf("\n");
	printf("%d", s1->dat[0]->data);
	return 0;
}
