#include<stdio.h>
#include<string.h>
int b[27];

int main(){
	FILE *fin = NULL, *fout = NULL;
	if((fin = fopen("encrypt.txt", "r")) == NULL){
		printf("in error\n");
		return 0;
	}
	if((fout = fopen("output.txt", "w")) == NULL){
		printf("out error\n");
		return 0;
	}
	char a[55], buf[200], ans[200];
	int lena, cnt=0, lenb;
	scanf("%s", a);
	lena = strlen(a);
	for(int i=0; i<lena; i++){
		if(b[a[i]-'a'+1] == 0){
			a[cnt++] = a[i];
			b[a[i]-'a'+1] = 1;
		}
	}
	for(int i=26; i>=1; i--){
		if(b[i] == 0){
			a[cnt++] = 'a'-1+i;
		}
	}
	while(fgets(buf, 200, fin) != NULL){
		cnt = 0;
		lenb = strlen(buf);
		for(int i=0; i<lenb; i++){
			if(buf[i]>='a' && buf[i]<='z')
				ans[cnt++] = a[buf[i]-'a'];
			else
				ans[cnt++] = buf[i];
		}
		ans[cnt] = '\0';
		fputs(ans, fout);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
