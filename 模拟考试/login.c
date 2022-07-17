#include<stdio.h>
#include<stdlib.h>

struct stu{
	int num;
	char name[20];
	int id;
	char date[10];
}s[205];

int visited[205];

int cmp(const void *p1, const void *p2){
	return ((struct stu*)p1)->num - ((struct stu*)p2)->num;
}

int main(){
	int n, f;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%d%s%d%s", &s[i].num, s[i].name, &s[i].id, s[i].date);
	}
	qsort(s, n, sizeof(s[0]), cmp);
	for(int i=0;i<n;i++){
		if(visited[i] == 0){
			f = 0;
			visited[i] = 1;
			for(int j=i+1;j<n;j++){
				if(s[j].num == s[i].num){
					visited[j] = 1;
					if(s[j].id != s[i].id){
						f = 1;
					}
				}
			}
			if(f){
				printf("%d %s\n", s[i].num, s[i].name);
			}
		}
	}
	return 0;
}
