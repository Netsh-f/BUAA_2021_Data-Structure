#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

char opeExit[] = {"exit"}, opePrint[] = {"print"};
int top = -1;
double xVal[MAX];

struct stack{
	double a[MAX];
	int top;
}*num, *ope;

struct stack *create(){
	struct stack *p;
	p = (struct stack*)malloc(sizeof(struct stack));
	p->top = -1;
	return p;
};

void push(struct stack *p, double x){
	p->a[++(p->top)] = x;
}
double pop(struct stack *p){
	return p->a[(p->top)--];
}
double topVal(struct stack *p){
	return p->a[p->top];
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
		if(priority(x) > priority(topOpe) || ope->top == -1 || x == '('){
			push(ope, x);
		}else{
			while(priority(x) <= priority(topOpe)){
				ans = caculate(topOpe);
				pop(ope);
				push(num, ans);
				if(ope->top == -1){
					break;
				}
				topOpe = topVal(ope);
			}
			push(ope, x);
		}
	}
}

double cal(char s[]){
	int lens = strlen(s), f = 0;
	double val = 0;
	num = create();
	ope = create();
	for(int i=0;i<lens;i++){
		if(s[i] >= '0' && s[i] <= '9'){
			val = val*10 + s[i]-'0';
			f = 1;
		}else if(s[i] >= 'a' && s[i] <= 'z'){
			val = xVal[(int)s[i]];
			f = 1;
		}else{
			if(f){
				f = 0;
				push(num, val);
				val = 0;
			}
			dealOpe(s[i]);
		}
	}
	if(f){
		push(num, val);
	}
	while(ope->top != -1){
		push(num, caculate(pop(ope)));
	}
	return num->a[0];
}

int main(){
	char buf[205];
	int lenb, f;
	while(1){
		gets(buf);
		if(strcmp(buf, opeExit) == 0){
			break;
		}else if(buf[1] == '='){
			xVal[(int)buf[0]] = cal(buf+2);
		}else if(strncmp(buf, opePrint, 5) == 0){
			lenb = strlen(buf);
			f = 0;
			for(int i=6;i<lenb;i++){
				if(buf[i] >= 'a' && buf[i] <= 'z'){
					if(f)
						printf(" ");
					printf("%.3f", xVal[(int)buf[i]]);
					f = 1;
				}
			}
			printf("\n");
		}
	}
	return 0;
}
