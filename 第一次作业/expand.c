#include<stdio.h>
#include<string.h>

int main(){
	char s[2000],ans[2000];
	int lens,cnt=0,t;
	scanf("%s",s);
	lens=strlen(s);
	for(int i=0;i<lens;i++){
		if(s[i]=='-'&&i+1<=lens-1&&s[i+1]>s[i-1]&&((s[i-1]>='a'&&s[i-1]<='z'&&s[i+1]>='a'&&s[i+1]<='z')||(s[i-1]>='A'&&s[i-1]<='Z'&&s[i+1]>='A'&&s[i+1]<='Z')||(s[i-1]>='0'&&s[i-1]<='9'&&s[i+1]>='0'&&s[i+1]<='9'))){
			t=1;
			while(s[i-1]+t!=s[i+1]){
				ans[cnt++]=s[i-1]+t;
				t++;
			}
			ans[cnt++]=s[i+1];
			i++;
		}else{
			ans[cnt++]=s[i];
		}
	}
	ans[cnt]='\0';
	printf("%s\n",ans);
	return 0;
}
