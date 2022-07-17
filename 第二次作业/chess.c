#include<stdio.h>
#include<string.h>
int a[21][21]={0};

int f(int m,int n){
	int f=0,t=a[m][n];
	if(a[m][n]!=0){
		for(int i=0;i<3;i++){
			if(a[m][n+1+i]==t){
				if(i==2&&(a[m][n-1]==0||a[m][n+4]==0)){
					f=1;
					break;
				}
				continue;
			}else{
				break;
			}
		}
		for(int i=0;i<3;i++){
			if(a[m+1+i][n]==t){
				if(i==2&&(a[m-1][n]==0||a[m+4][n]==0)){
					f=1;
					break;
				}
				continue;
			}else{
				break;
			}
		}
		for(int i=0;i<3;i++){
			if(a[m+1+i][n+1+i]==t){
				if(i==2&&(a[m-1][n-1]==0||a[m+4][n+4]==0)){
					f=1;
					break;
				}
				continue;
			}else{
				break;
			}
		}
		for(int i=0;i<3;i++){
			if(a[m+1+i][n-1-i]==t){
				if(i==2&&(a[m-1][n+1]==0||a[m+4][n-4]==0)){
					f=1;
					break;
				}
				continue;
			}else{
				break;
			}
		}
	}else{
		return 0;
	}
	if(f)
		return 1;
	else
		return 0;
}

int main(){
	int t;
	for(int i=0;i<=20;i++){
		a[0][i]=3;
		a[i][0]=3;
		a[20][i]=3;
		a[i][20]=3;
	}
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++){
			t=f(i,j);
			if(t!=0){
				printf("%d:%d,%d\n",a[i][j],i,j);
				return 0;
			}
		}
	printf("No\n");
	return 0;
}
