#include<stdio.h>
#include<string.h>
void f(char *s,char *t){
	int n=strlen(s);
	while(*(s+n)=*t){
		s++; t++;
	}
}
int main(){
	char a[100],b[100];
	scanf("%s%s",a,b);
	f(a,b);
	printf("%s",a);
}
