#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	char name[25];
	int f[11];
	int fnum;
}foun[105];

int cntf;
int stack[205];
int top = -1;

int located(char s[]){
	for(int i=0;i<cntf;i++){
		if(strcmp(s, foun[i].name) == 0){
			return i;
		}
	}
	return cntf;
}

void push(int id){
	int f = 0;
	stack[++top] = id;
	if(top > 0){
		int p = stack[top-1];
		for(int i=0;i<foun[p].fnum;i++){
			if(id == foun[p].f[i]){
				f = 1;
			}
		}
		if(f == 0){
			foun[p].f[foun[p].fnum++] = id;
		}
	}
}

void pop(){
	if(top >= 0){
		top--;
	}
}

void add(char s[]){
	strcpy(foun[cntf++].name, s);
}

int main(){
	int ope, f;
	char name[25];
	do{
		scanf("%d", &ope);
		if(ope == 8){
			scanf("%s", name);
			if(located(name) == cntf){
				add(name);
			}
			push(located(name));
		}else if(ope == 0){
			pop();
		}
	}while(top != -1);
	for(int i=0;i<cntf;i++){
		if(foun[i].fnum > 0){
			f = 0;
			printf("%s:", foun[i].name);
			for(int j=0;j<foun[i].fnum;j++){
				if(f == 0){
					f = 1;
					printf("%s", foun[foun[i].f[j]].name);
				}else{
					printf(",%s", foun[foun[i].f[j]].name);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
