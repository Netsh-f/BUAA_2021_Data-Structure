#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

struct alGraph{
	struct vNode vertices[MVnum];
	int vexnum, arcnum;
};

int locateVex(struct alGraph G, int v){
	for(int i=0;i<G.vexnum;i++){
		if(G.vertices[i].data == v){
			return i;
		}
	}
	return 0;
}

void create(struct alGraph *G){
	int i, j;
	printf("�����ܶ������ͱ�����\n");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	printf("����������ֵ��\n");
	for(int i=0;i<G->vexnum;i++){
		scanf("%d", &G->vertices[i].data);
		G->vertices[i].firstArc = NULL;
	}
	printf("�ֱ�������������ӵ���������:\n");
	for(int k=0;k<G->arcnum;k++){
		scanf("%d%d", &i, &j);
		struct arcNode *p1 = (struct arcNode*)malloc(sizeof(struct arcNode));
		p1->adjvex = j;
		p1->nextArc = G->vertices[i].firstArc;
		G->vertices[i].firstArc = p1;
		struct arcNode *p2 = (struct arcNode*)malloc(sizeof(struct arcNode));
		p2->adjvex = i;
		p2->nextArc = G->vertices[j].firstArc;
		G->vertices[j].firstArc = p2;
	}
}

void print(struct alGraph *G){
	printf("----����ڽӱ�----\n");
	struct arcNode *p;
	for(int i=0;i<G->vexnum;i++){
		printf("����%d:\n", G->vertices[i].data);
		p = G->vertices[i].firstArc;
		while(p != NULL){
			printf("-����-%d-", p->adjvex);
			p = p->nextArc; 
		}
		printf("\n");
	}
}

int main(){
	struct alGraph G;
	create(&G);
	print(&G);
	return 0;
}
