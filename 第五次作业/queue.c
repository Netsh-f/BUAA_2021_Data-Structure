#include<stdio.h>

int q[200050], front, rear, win = 3, a[2000];

void del(int x){
	if(rear-front>x){
		front += x;
	}else{
		front = rear;
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n;i++){
		rear += a[i];
		if((rear-front)/win>=7 && win<5){
			win++;
		}
		if((rear-front)/win>=7 && win<5){
			win++;
		}
		del(win);
		if((rear-front)/win<7 && win>3){
			win--;
		}
		if((rear-front)/win<7 && win>3){
			win--;
		}
		for(int i=front+1;i<=rear;i++){
			q[i]++;
		}
	}
	while(1){
		del(win);
		if((rear-front)/win<7 && win>3){
			win--;
		}
		for(int i=front+1;i<=rear;i++){
			q[i]++;
		}
		if(front==rear){
			break;
		}
	}
	for(int i=1;i<=rear;i++){
		printf("%d : %d\n",i,q[i]);
	}
	return 0;
}
