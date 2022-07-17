#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int l,r;
}m[105];

int cmp(const void *p1, const void *p2){
	struct node *p3 = (struct node*)p1;
	struct node *p4 = (struct node*)p2;
	return p3->l - p4->l;
}


int main(){
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%d %d", &m[i].l, &m[i].r);
	}
	qsort(m, n, sizeof(m[0]), cmp);
	for(int i=0;i<n-1;i++){
		if(m[i].r == m[i+1].l - 1){
			m[i].r = m[i+1].r;
			for(int j=i+1;j<n-1;j++){
				m[j] = m[j+1];
			}
			i--; n--;
		}
	}
	for(int i=0;i<n;i++){
		printf("%d %d\n", m[i].l, m[i].r);
	}
	return 0;
}
