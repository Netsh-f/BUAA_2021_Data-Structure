#include<stdio.h>
#include<string.h>
char ch[105], a[50];

int main(){
	int m = 0, n = 0, cntm = 1, cntn = 1, lenc;
	char c = 0;
	gets(a);
	gets(ch);
	lenc = strlen(ch);
	if(a[1] == '-'){
		c = a[2];
		while(1){
			if(c>='0' && c<='9'){
				m = m * 10 + c -'0';
				c = a[2+cntm];
				cntm++;
			}else{
				cntm--;
				break;
			}
		}
		c = a[3+cntm];
		while(1){
			if(c>='0' && c<='9'){
				n = n * 10 + c -'0';
				c = a[3+cntm+cntn];
				cntn++;
			}else{
				cntn--;
				break;
			}
		}

		if(m<lenc){
			for(int i=0;i<n-m;i++){
				printf("#");
			}
		}else{
			for(int i=0;i<n-lenc;i++){
				printf("#");
			}
		}
		for(int i=0;i<m && i<lenc;i++){
			printf("%c",ch[i]);
		}
		printf("\n");
	}else{
		c = a[1];
		while(1){
			if(c>='0' && c<='9'){
				m = m * 10 + c -'0';
				c = a[1+cntm];
				cntm++;
			}else{
				cntm--;
				break;
			}
		}
		c = a[2+cntm];
		while(1){
			if(c>='0' && c<='9'){
				n = n * 10 + c -'0';
				c = a[2+cntm+cntn];
				cntn++;
			}else{
				cntn--;
				break;
			}
		}
		
		for(int i=0;i<m && i<lenc;i++){
			printf("%c",ch[i]);
		}
		if(m<lenc){
			for(int i=0;i<n-m;i++){
				printf("#");
			}
		}else{
			for(int i=0;i<n-lenc;i++){
				printf("#");
			}
		}
		printf("\n");
	}
	return 0;
}
