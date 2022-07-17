#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hamming{
	char s[20];
	int lenh;
}ham[20];

int f(char a[], char b[]){
	int len = strlen(a);
	int h = 0;
	for(int i=0;i<len;i++){
		if(a[i] != b[i]){
			h++;
		}
	}
	return h;
}

int cmp(const void *p1, const void *p2){
	if(((struct hamming*)p1)->lenh == ((struct hamming*)p2)->lenh){
		return strcmp(((struct hamming*)p1)->s, ((struct hamming*)p2)->s);
	}
	return ((struct hamming*)p2)->lenh - ((struct hamming*)p1)->lenh;
}

int main(){
	int n;
	char s0[20];
	scanf("%d%s", &n, s0);
	for(int i=0;i<n-1;i++){
		scanf("%s", ham[i].s);
		ham[i].lenh = f(ham[i].s, s0);
	}
	qsort(ham, n-1, sizeof(ham[0]), cmp);
	for(int i=0;i<n-1;i++){
		printf("%s %s %d\n", s0, ham[i].s, ham[i].lenh);
	}
	return 0;
}
