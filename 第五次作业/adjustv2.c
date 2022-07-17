#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ch[205][4], chn[205], data[205], cntd = 0, index[205], cnti = 1;
int q[205], front, rear;

int main(){
	int n, c, t;
	while(1){
		scanf("%d", &n);
		if(n == -1)
			break;
		scanf("%d", &c);
		while(c != -1){
			chn[n]++;
			if(c < 100)
				cntd++;
			ch[n][chn[n]] = c;
			scanf("%d", &c);
		}
	}
	for(int i=0;i<cntd;i++){
		scanf("%d %d", &n, &c);
		data[n] = c;
		index[cnti++] = n;
	}
	cnti = 1;
	for(int i=1;i<=cntd;i++){
		for(int j=1;j<=cntd-i;j++){
			if(data[index[j]] < data[index[j+1]] || (data[index[j]] == data[index[j+1]] && index[j] > index[j+1])){
				t = index[j];
				index[j] = index[j+1];
				index[j+1] = t;
			}
		}
	}
	
	q[++rear] = 100;
	while(front != rear){
		n = q[++front];
		for(int i=1;i<=chn[n];i++){
			q[++rear] = ch[n][i];
		}
		if(n < 100){
			printf("%d->%d\n", index[cnti++], n);
		}
	}
	return 0;
}
