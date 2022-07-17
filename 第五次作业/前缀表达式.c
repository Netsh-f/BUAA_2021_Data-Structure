#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
	int data[2000];
	int top;
}*s1, *s2;

struct stack *createStack(){
	struct stack *p;
	p = (struct stack*)malloc(sizeof(struct stack));
	p->top = -1;
	return p;
}

void push(struct stack *p, int x){
	p->top++;
	p->data[p->top] = x;
}

int pop(struct stack *p){
	p->top--;
	return p->data[p->top+1];
}

int topVal(struct stack *p){
	return p->data[p->top];
}

int isOpe(char c){
	return c=='('||c==')'||c=='+'||c=='-'||c=='*'||c=='/';
}

int priority(char c){
	switch(c){
		case ')': return 0;
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		default: return -1;
	}
}

int main(){
	char str[1005];
	int val = 0, f = 0, lens, w = 1;
	s1 = createStack(); s2 = createStack();
	gets(str);
	lens = strlen(str);
	for(int i=lens-1;i>=0;i--){
		if(str[i]>='0' && str[i]<='9'){
			val = val + (str[i] - '0') * w;
			w = w * 10;
			f = 1;
		}else{
			if(f){
				f = 0;
				push(s2, val);
				val = 0; w = 1;
			}
			if(isOpe(str[i])){
				if(str[i] == ')'){
					push(s1, str[i]);
				}else if(str[i] == '('){
					while(topVal(s1) != ')'){
						push(s2, pop(s1));
					}
					pop(s1);
				}else{
					while(priority(topVal(s1)) > priority(str[i])){
						push(s2, pop(s1));
					}
					push(s1, str[i]);
				}
			}
		}
	}
	while(s1->top>=0){
		push(s2, pop(s1));
	}
	for(int i=s2->top;i>=0;i--){
		if(isOpe(s2->data[i])){
			printf("%c ", s2->data[i]);
		}else{
			printf("%d ", s2->data[i]);
		}
	}
	return 0;
}
