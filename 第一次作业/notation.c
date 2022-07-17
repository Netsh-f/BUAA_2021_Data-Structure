#include<stdio.h>
#include<string.h>

int main(){
	char s[250];
	int dot,num=-1,lens,f=0,f1=0;
	scanf("%s",s);
	lens=strlen(s);
	for(int i=0;i<lens;i++){
		if(s[i]=='.') dot=i;
		if(s[i]>='1'&&s[i]<='9'&&num==-1) num=i;
	}
	for(int i=0;i<lens;i++){
		if(f&&f1==0){
			printf(".");
			f1=1;
		}
		if(f&&s[i]!='.')
			printf("%c",s[i]);
		if(s[i]!='.'&&s[i]!='0'&&f==0){
			printf("%c",s[i]);
			f=1;
		}
	}
	printf("e%d\n",dot-num-1<0?dot-num:dot-num-1);
	return 0;
}
