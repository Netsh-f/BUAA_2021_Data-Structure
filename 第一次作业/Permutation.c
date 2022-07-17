#include<stdio.h>
int a[11],b[11];

void f(int p,int n){
	if(p==n+1){
		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
		return;
	}
	for(int i=1;i<=n;i++){
		if(b[i]==0){
			a[p]=i;
			b[i]=1;
			f(p+1,n);
			b[i]=0;
		}
	}
}

int main(){
	int N;
	scanf("%d",&N);
	f(1,N);
	return 0;
}
