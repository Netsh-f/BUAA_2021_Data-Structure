#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int b[105];

struct tel{
	char name[25];
	char num[20];
	int k;
};

int cmp(const void *x,const void *y){
	struct tel *a=(struct tel*)x;
	struct tel *b=(struct tel*)y;
	if(strcmp(a->name,b->name)==0){
		return a->k-b->k;
	}else{
		return strcmp(a->name,b->name);
	}
}

int main(){
	int n,cnt;
	struct tel a[105];
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s%s",a[i].name,a[i].num);
		a[i].k=0;
	}
	for(int i=0;i<n;i++){
		b[i]=1;
		cnt=0;
		for(int j=i+1;j<n;j++){
			if(strcmp(a[i].name,a[j].name)==0&&b[j]==0){
				b[j]=1;
				if(strcmp(a[i].num,a[j].num)==0){
					a[j].k=-1;
				}else{
					a[j].k=++cnt;
				}
			}
		}
	}
	qsort(a,n,sizeof(a[0]),cmp);
	for(int i=0;i<n;i++){
		if(a[i].k!=-1){
			if(a[i].k==0){
				printf("%s %s\n",a[i].name,a[i].num);
			}else{
				printf("%s_%d %s\n",a[i].name,a[i].k,a[i].num);
			}
		}
	}
	return 0;
}
