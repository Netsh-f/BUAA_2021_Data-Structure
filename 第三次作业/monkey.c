#include<stdio.h>

int next[105];

int main(){
	int n,m,q;
	scanf("%d%d%d", &n, &m, &q);
	for(int i=1;i<n;i++){
		next[i] = i+1;
	}
	next[n] = 1;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<m-2;j++){
			q = next[q];
		}
		next[q] = next[next[q]];
		q = next[q];
	}
	printf("%d\n",q);
	return 0;
}
