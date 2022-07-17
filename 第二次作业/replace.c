#include<stdio.h>
#include<string.h>

int strncmpA(char *a, char *b, int n){
	for(int i=0; i<n; i++){
		if((*(a+i) == *(b+i))||(*(a+i)-'A'+'a' == *(b+i))||(*(a+i)-'a'+'A' == *(b+i)))
			continue;
		else
			return 1;
	}
	return 0;
}

int main(){
	FILE *f = NULL, *fout = NULL;
	char a[2000], in[200], out[200], ans[2000];
	int lena, lenin, lenout, cnt=0;
	scanf("%s%s", in, out);
	lenin = strlen(in); lenout = strlen(out);
	if((f = fopen("filein.txt", "r")) == NULL){
		printf("fopen in error\n");
		return 0;
	}
	if((fout = fopen("fileout.txt", "w")) == NULL){
		printf("fopen out error\n");
		return 0;
	}
	while(fgets(a, 2000, f) != NULL){
		lena = strlen(a);
		for(int i=0; i < lena; i++){
			if(strncmpA(a+i, in, lenin) == 0){
				i += lenin - 1;
				for(int j=0; j < lenout; j++){
					ans[cnt++] = out[j];
				}
			}else{
				ans[cnt++] = a[i];
			}
		}
		ans[cnt] = '\0';
		fputs(ans, fout);
		cnt = 0;
	}
	fclose(fout);
	fclose(f);
	return 0;
}
