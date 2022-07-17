#include<stdio.h>
#include<string.h>
char stack[205][2], buf[205], ans[205];
int top = 0, f1 = 0, f2 = 0, cnt = 0;

int is(char c){
	return c == '{' || c == '}' || c == '(' || c == ')';
}

int main(){
	FILE *f = fopen("example.c", "r");
	int lenb, line = 0;
	while(fgets(buf, 205, f) != NULL){
		lenb = strlen(buf);
		line++;
		for(int i=0;i<lenb;i++){
			if(buf[i] == '/' && buf[i+1] == '/'){
				if(f1 == 1 || f2 == 1){
					continue;
				}
				break;
			}
			if(buf[i] == '\'' && buf[i+2] == '\''){
				if(f1 == 1 || f2 == 1){
					continue;
				}
				i = i+2;
			}
			if(buf[i] == '\"'){
				if(f2 == 1)
					continue;
				if(f1 == 0){
					f1 = 1;
				}else{
					f1 = 0;
				}
			}
			if(buf[i] == '/' && buf[i+1] == '*'){
				if(f1 == 1)
					continue;
				if(f2 == 0){
					f2 = 1;
					i++;
				}
			}
			if(buf[i] == '*' && buf[i+1] == '/'){
				if(f2 == 1){
					f2 = 0;
					i++;
				}
			}
			if(is(buf[i])){
				if(f1 == 1 || f2 == 1){
					continue;
				}
				if(top == 0){
					if(buf[i] == '(' || buf[i] == '{'){
						stack[top][0] = buf[i];
						stack[top][1] = line;
						ans[cnt++] = buf[i];
						top++;
					}else if(buf[i] == ')' || buf[i] == '}'){
						printf("without maching '%c' at line %d\n", buf[i], line);
						return 0;
					}
				}else{
					if(buf[i] == '('){
						stack[top][0] = buf[i];
						stack[top][1] = line;
						ans[cnt++] = buf[i];
						top++;
					}else if(buf[i] == '{'){
						if(stack[top-1][0] == '('){
							printf("without maching '%c' at line %d\n", stack[top-1][0], stack[top-1][1]);
							return 0;
						}else{
							stack[top][0] = buf[i];
							stack[top][1] = line;
							ans[cnt++] = buf[i];
							top++;
						}
					}else if(buf[i] == ')'){
						if(stack[top-1][0] == '('){
							top--;
							ans[cnt++] = buf[i];
						}else{
							printf("without maching '%c' at line %d\n", buf[i], line);
							return 0;
						}
					}else if(buf[i] == '}'){
						if(stack[top-1][0] == '{'){
							top--;
							ans[cnt++] = buf[i];
						}else{
							printf("without maching '%c' at line %d\n", buf[i], line);
							return 0;
						}
					}
				}
			}
		}
	}
	if(top != 0){
		printf("without maching '%c' at line %d\n", stack[top-1][0], stack[top-1][1]);
	}else{
		for(int i=0;i<cnt;i++){
			printf("%c",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
