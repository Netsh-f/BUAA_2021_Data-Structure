#include<stdio.h>
int a[105], top = 0;

int main(){
	int n, x;
	scanf("%d",&n);
	while(n != -1){
		if(n == 1){
			scanf("%d",&x);
			if(top>=100){
				printf("error ");
			}else{
				a[top] = x;
				top++;
			}
		}else if(n == 0){
			if(top == 0){
				printf("error ");
			}else{
				printf("%d ",a[top - 1]);
				top--;
			}
		}
		scanf("%d",&n);
	}
}
