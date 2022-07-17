#include<stdio.h>
#include<stdlib.h>
#define MAX 205

struct stack{
	double a[MAX];
	int top;
}*num, *ope;

struct stack *create(){
	struct stack *p;
	p = (struct stack*)malloc(sizeof(struct stack));
	p->top = 0;
	return p;
};

void push(struct stack *p, double x){
	p->a[p->top] = x;
	p->top++;
}

double pop(struct stack *p){
	p->top--;
	return p->a[p->top];
}

double topVal(struct stack *p){
	return p->a[p->top-1];
}

int priority(char x){
	switch(x){
		case '(': return 0;
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		default: return -1;
	}
}

double caculate(char x){
	double p, q, ans = 0;
	q = pop(num);
	p = pop(num);
	switch(x){
		case '+':
			ans = p + q;
			break;
		case '-':
			ans = p - q;
			break;
		case '*':
			ans = p * q;
			break;
		case '/':
			ans = p / q;
			break;
	}
	return ans;
}

void dealOpe(char x){
	char topOpe = topVal(ope);
	double ans;
	if(x == ')'){
		while(topOpe != '('){
			ans = caculate(topOpe);
			pop(ope);
			push(num, ans);
			topOpe = topVal(ope);
		}
		pop(ope);
	}else{
		if(priority(x) > priority(topOpe) || ope->top == 0 || x == '('){
			push(ope, x);
		}else{
			while(priority(x) <= priority(topOpe)){
				ans = caculate(topOpe);
				pop(ope);
				push(num, ans);
				if(ope->top == 0){
					break;
				}
				topOpe = topVal(ope);
			}
			push(ope, x);
		}
	}
}

int main(){
	char str[205], topOpe;
	double val = 0, f = 0, ans;
	num = create();
	ope = create();
	gets(str);
	for(int i=0;str[i]!='=';i++){
		if(str[i] >= '0' && str[i] <= '9'){
			val *= 10;
			val += str[i] - '0';
			f = 1;
		}else{
			if(f){
				f = 0;
				push(num, val);
				val = 0;
			}
			if(str[i] == ' ' )
				continue;
			dealOpe(str[i]);
		}
	}
	if(f){
		push(num, val);
	}
	while(ope->top != 0){
		topOpe = pop(ope);
		ans = caculate(topOpe);
		push(num, ans);
	}
	printf("%.2f", num->a[0]);
	return 0;
}
