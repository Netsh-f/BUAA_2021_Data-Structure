#include<stdio.h>
#include<string.h>
int main(){
	char a[]="24 / ( 1 + 5/3 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 )=";
	for(int i=0;i<(int)strlen(a);i++){
		printf("%d\n",' ');
	}
	return 0;
}
