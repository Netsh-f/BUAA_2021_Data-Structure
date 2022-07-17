#include<stdio.h>
#include<stdlib.h>
#define MVnum 100

struct arcNode{
	int adjvex;
	struct arcNode *nextArc;
	int weight;
};

struct vNode{
	int data;
	struct arcNode *firstArc;
};

struct graph{
	int vexNum;
	int arcNum;
	struct vNode vertices[MVnum];
};

void create(struct graph *G){
	printf("vexNum and arcNum:\n");
	scanf("%d%d", &G->vexNum, &G->arcNum);
}
