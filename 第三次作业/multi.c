#include<stdio.h>
#include<stdlib.h>

int data1[2000][2];
int data2[2000][2];

struct x{
	int a;
	int b;
	struct x *next;
	struct x *prev;
}*head;

void insert(int p, int q){
	if(head->next == NULL){
		struct x *pnew = (struct x*)malloc(sizeof(struct x));
		pnew->a = p;
		pnew->b = q;
		pnew->next = NULL;
		pnew->prev = head;
		head->next = pnew;
	}else{
		for(struct x *i = head->next; i != NULL; i = i->next){
			if(q < i->b){
				if(i->next == NULL){
					struct x *pnew = (struct x*)malloc(sizeof(struct x));
					pnew->a = p;
					pnew->b = q;
					pnew->prev = i;
					pnew->next = NULL;
					i->next = pnew;
					break;
				}else
					continue;
			}
			if(q == i->b){
				i->a += p;
				break;
			}
			if(q > i->b){
				struct x *pnew = (struct x*)malloc(sizeof(struct x));
				pnew->a = p;
				pnew->b = q;
				pnew->prev = i->prev;
				pnew->next = i;
				i->prev->next = pnew;
				i->prev = pnew;
				break;
			}
		}
	}
}

int main(){
	int n1 = 0, n2 = 0;
	char c = ' ';
	head = (struct x*)malloc(sizeof(struct x));
	head->next = head->prev = NULL;
	while(c!='\n'){
		scanf("%d %d", &data1[n1][0], &data1[n1][1]);
		c = getchar();
		n1++;
	}
	c = ' ';
	while(c!='\n'){
		scanf("%d %d", &data2[n2][0], &data2[n2][1]);
		c = getchar();
		n2++;
	}
	for(int i=0;i<n1;i++){
		for(int j=0;j<n2;j++){
			insert(data1[i][0]*data2[j][0], data1[i][1]+data2[j][1]);
		}
	}
	for(struct x *i = head->next; i != NULL; i = i->next){
		printf("%d %d ",i->a, i->b);
	}
	return 0;
}
