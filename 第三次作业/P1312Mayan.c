#include<stdio.h>

struct Map{
	int a[6][8];
}map[6];
int b[6][8],ans[6][3];
int n;

void display(int step){
	printf("\nstep = %d\n",step);
	for(int j=6;j>=0;j--){
		for(int i=0;i<5;i++){
			printf("%d ",map[step].a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void clear(int step){	
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(i+2<5&&map[step].a[i][j]!=0&&map[step].a[i][j]==map[step].a[i+1][j]&&map[step].a[i+1][j]==map[step].a[i+2][j]){
				b[i][j]=1; b[i+1][j]=1; b[i+2][j]=1;
			}
			if(j+2<7&&map[step].a[i][j]!=0&&map[step].a[i][j]==map[step].a[i][j+1]&&map[step].a[i][j+2]==map[step].a[i+2][j]){
				b[i][j]=1; b[i+1][j]=1; b[i+2][j]=1;
			}
		}
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(b[i][j]==1){
				map[step].a[i][j]=0;
				b[i][j]=0;
			}
		}
	}
}

void falls(int step){
	int num=0;
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(map[step].a[i][j]==0){
				num++;
			}else{
				if(num){
					map[step].a[i][j-num]=map[step].a[i][j];
					map[step].a[i][j]=0;
					j-=num;
					num=0;
				}
			}
		}
		num=0;
	}
}

void fall(int step){
	for(int i=0;i<5;i++){
		int num=0;
		for(int j=0;j<7;j++){
			if(map[step].a[i][j]!=0){
				map[step].a[i][num++]=map[step].a[i][j];
			}
		}
		for(int j=num;j<7;j++){
			map[step].a[i][j]=0;
		}
	}
}

int move(int x,int y,int dir,int step){
	map[step]=map[step-1];
	int t;
	if(dir==1){
		if(x==4){
			return 0;
		}
		t=map[step].a[x][y];
		map[step].a[x][y]=map[step].a[x+1][y];
		map[step].a[x+1][y]=t;
	}else if(dir==-1){
		if(x==0){
			return 0;
		}
		t=map[step].a[x][y];
		map[step].a[x][y]=map[step].a[x-1][y];
		map[step].a[x-1][y]=t;
	}
	clear(step);
	fall(step);
	clear(step);
	return 1;
}

int f(int step){
	int valf=0;
	if(step==n){
		for(int i=0;i<5;i++){
			for(int j=0;j<7;j++){
				if(map[n].a[i][j]){
					return 0;
				}
			}
		}
		return 1;
	}
	fall(step);
	clear(step);
	fall(step);
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(map[step].a[i][j]==0){
				continue;
			}else{
				if(move(i,j,1,step+1)==1){
					valf=f(step+1);
					if(valf){
						ans[step][0]=i;
						ans[step][1]=j;
						ans[step][2]=1;
						return 1;
					}
				}
				if(move(i,j,-1,step+1)==1){
					valf=f(step+1);
					if(valf){
						ans[step][0]=i;
						ans[step][1]=j;
						ans[step][2]=-1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


int main(){
	scanf("%d",&n);
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			scanf("%d",&map[0].a[i][j]);
			if(map[0].a[i][j]==0){
				break;
			}
		}
	}
	f(0);
	for(int i=0;i<n;i++){
		printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
	}
	return 0;
}
