#include<stdio.h>
#include<stdlib.h>

struct point{
	int x;
	int y;
	struct point *line1;
	struct point *line2;
	struct point *next;
	int b;
}*ph, *tail;

void input(struct point *p){
	if(ph == NULL){
		ph = p;
		tail = p;
	}else{
		tail->next = p;
		p->next = NULL;
		tail = p;
	}
}

int main(){
	int n,x1,y1,x2,y2;
	ph = tail = NULL;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d%d%d",&x1, &y1, &x2, &y2);
		struct point *p1 = NULL;
		struct point *p2 = NULL;
		for(struct point *j = ph; j != NULL; j = j->next){
			if(j->x == x1 && j->y == y1){
				p1 = j;
			}
			if(j->x == x2 && j->y == y2){
				p2 = j;
			}
		}
		if(p1 == NULL){
			p1 = (struct point*)malloc(sizeof(struct point));
			p1->x = x1;
			p1->y = y1;
			p1->line1 = p1->line2 = NULL;
			p1->b = 0;
			input(p1);
		}
		if(p2 == NULL){
			p2 = (struct point*)malloc(sizeof(struct point));
			p2->x = x2;
			p2->y = y2;
			p2->line1 = p2->line2 = NULL;
			p2->b = 0;
			input(p2);
		}
		p1->line1 = p2;
		p2->line2 = p1;
	}
	
	int xm,ym,lm=0,len=0;
	for(struct point *i = ph; i != NULL; i = i->next){
		len = 0;
		if(i->b == 0){
			i->b = 1;
			for(struct point *j = i->line1; j != NULL; j = j->line1){
				len++;
				j->b = 1;
			}
			for(struct point *j = i->line2; j != NULL; j = j->line2){
				len++;
				j->b = 1;
				if(len > lm){
					xm = j->x;
					ym = j->y;
					lm = len;
				}
			}
			if(i->line2 == NULL && len > lm){
				xm = i->x;
				ym = i->y;
				lm = len;
			}
		}
	}
	printf("%d %d %d\n", lm, xm, ym);
	return 0;
}
