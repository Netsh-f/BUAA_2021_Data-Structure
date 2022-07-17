#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 1005
int visited[Max], cnt = 0;
char path[Max], pathAns[Max][Max];

struct arcNode{
	int adjvex;
	struct arcNode *nextArc;
	int num;
};

struct vexNode{
	int data;
	struct arcNode *firstArc;
};

struct graph{
	struct vexNode vertices[Max];
	int vexNum, arcNum;
};

void addArc(struct graph *G, int x, int y, int val){
	struct arcNode *p1 = (struct arcNode*)malloc(sizeof(struct arcNode));
	p1->adjvex = y;
	p1->nextArc = G->vertices[x].firstArc;
	p1->num = val;
	G->vertices[x].firstArc = p1;
	struct arcNode *p2 = (struct arcNode*)malloc(sizeof(struct arcNode));
	p2->adjvex = x;
	p2->nextArc = G->vertices[y].firstArc;
	p2->num = val;
	G->vertices[y].firstArc = p2;
}

void printPath(int n){
	strncpy(pathAns[cnt], path, n);
	cnt++;
}

int cmp(const void *p1, const void *p2){
	char *p3 = (char*)p1;
	char *p4 = (char*)p2;
	return strcmp(p3, p4);
}

void DFS(struct graph *G, int vex, int depth){
	if(vex == G->vexNum-1){
		printPath(depth);
		return;
	}else{
		struct arcNode *p;
		for(p = G->vertices[vex].firstArc;p != NULL;p = p->nextArc){
			if(!visited[p->adjvex]){
				path[depth] = p->num;
				visited[p->adjvex] = 1;
				DFS(G, p->adjvex, depth+1);
				visited[p->adjvex] = 0;
			}
		}
	}
}

int main(){
	int val, x, y;
	struct graph *G = (struct graph*)malloc(sizeof(struct graph));
	scanf("%d%d", &G->vexNum, &G->arcNum);
	for(int i=0;i<G->vexNum;i++)
		G->vertices[i].firstArc = NULL;
	for(int i=0;i<G->arcNum;i++){
		scanf("%d%d%d", &val, &x, &y);
		addArc(G, x, y, val);
	}
	visited[0] = 1;
	DFS(G, 0, 0);
	qsort(pathAns, cnt, sizeof(pathAns[0]), cmp);
	for(int i=0;i<cnt;i++){
		for(int j=0;pathAns[i][j] != '\0';j++){
			printf("%d ", pathAns[i][j]);
		}
		printf("\n");
	}
	return 0;
}
