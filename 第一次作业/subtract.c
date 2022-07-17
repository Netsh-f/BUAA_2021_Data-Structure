#include<stdio.h>
#include<string.h>
char a[100],b[100],c[100];

void str(char s[],int len){
	int l=0,r=len-1,t;
	while(l<r){
		t=s[l];
		s[l]=s[r];
		s[r]=t;
		l++; r--;
	}
}

int main(){
	char *pa,*pb;
	scanf("%s%s",a,b);
	int lena=strlen(a),lenb=strlen(b),f=1,lenm=lena,f1=0;
	str(a,lena); str(b,lenb);
	for(int i=0;i<lena;i++)
		a[i]-='0';
	for(int i=0;i<lenb;i++)
		b[i]-='0';
	if(lena<lenb){
		f=0;
		lenm=lenb;
	}
	else if(lena==lenb)
		for(int i=lena;i>=0;i--)
			if(a[i]<b[i])
				f=0;
	if(f){
		pa=a; pb=b;
	}else{
		pa=b; pb=a;
	}
	for(int i=0;i<lena||i<lenb;i++){
		c[i]=c[i]+pa[i]-pb[i];
		if(c[i]<0){
			c[i+1]--;
			c[i]+=10;
		}
	}
	if(!f) printf("-");
	for(int i=lenm-1;i>=0;i--){
		if(f1) printf("%d",c[i]);
		if(c[i]!=0&&f1==0){
			f1=1;
			printf("%d",c[i]);
		}
	}
	if(f1==0) printf("0");
	return 0;
}
