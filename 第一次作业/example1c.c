#include<stdio.h>

int main(){
	char s[200];
	int l[200],cnt=0,i=0,t,f=0;
	gets(s);
	while(1){
		if(s[i]==' '){
			i++;
			continue;
		}
		t=0;
		while(s[i]>='0'&&s[i]<='9'){
			t=t*10+s[i]-'0';
			i++;
			f=1;
		}
		if(f){
			l[cnt++]=t;
			f=0;
		}
		if(s[i]=='+'){
			l[cnt++]=-1;
			i++;
		}else if(s[i]=='-'){
			l[cnt++]=-2;
			i++;
		}else if(s[i]=='*'){
			l[cnt++]=-3;
			i++;
		}else if(s[i]=='/'){
			l[cnt++]=-4;
			i++;
		}else if(s[i]=='='){
			l[cnt]=-5;
			break;
		}
	}
	for(i=0;i<cnt;i++){
		if(l[i]==-3){
			l[i-1]=l[i-1]*l[i+1];
			for(int j=i;j+2<cnt;j++)
				l[j]=l[j+2];
			cnt-=2;
			i--;
		}
		if(l[i]==-4){
			l[i-1]=l[i-1]/l[i+1];
			for(int j=i;j+2<cnt;j++)
				l[j]=l[j+2];
			cnt-=2;
			i--;
		}
	}
	for(i=0;i<cnt;i++){
		if(l[i]==-1){
			l[i-1]=l[i-1]+l[i+1];
			for(int j=i;j+2<cnt;j++)
				l[j]=l[j+2];
			cnt-=2;
			i--;
		}
		if(l[i]==-2){
			l[i-1]=l[i-1]-l[i+1];
			for(int j=i;j+2<cnt;j++)
				l[j]=l[j+2];
			cnt-=2;
			i--;
		}
	}
	printf("%d\n",l[0]);
	return 0;
}
