#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXVEX 105
int visited[MAXVEX], deleted[MAXVEX];

struct Mgraph{
	int vex[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int vexnum, arcnum;
};

void addArc(struct Mgraph *G, int a, int b){
	G->arc[a][b] = 1;
	G->arc[b][a] = 1;
}

void DFS(struct Mgraph *G, int x){
	if(visited[x]){
		return;
	}else{
		printf("%d ", x);
		visited[x] = 1;
		for(int i=0;i<G->vexnum;i++){
			if(!visited[i] && G->arc[x][i]){
				DFS(G, i);
			}
		}
	}
	
}

void DFSgraph(struct Mgraph *G){
	memset(visited, 0, sizeof(visited));
	for(int i=0;i<G->vexnum;i++){
		if(!visited[i] && !deleted[i]){
			DFS(G, i);
		}
	}
	printf("\n");
}

void BFSgraph(struct Mgraph *G){
	int Q[MAXVEX*2], front = 0, rear = 0, qt;
	memset(visited, 0, sizeof(visited));
	for(int i=0;i<G->vexnum;i++){
		if(!visited[i] && !deleted[i]){
			printf("%d ", i);
			visited[i] = 1;
			Q[++rear] = i;
			while(front != rear){
				qt = Q[++front];
				for(int j = 0;j<G->vexnum;j++){
					if(!visited[j] && G->arc[qt][j]){
						printf("%d ", j);
						visited[j] = 1;
						Q[++rear] = j;
					}
				}
			}
		}
	}
	printf("\n");
}

void delVex(struct Mgraph *G, int x){
	for(int i=0;i<G->vexnum;i++){
		G->arc[x][i] = 0;
		G->arc[i][x] = 0;
	}
	deleted[x] = 1;
}

int main(){
	struct Mgraph *G = (struct Mgraph*)malloc(sizeof(struct Mgraph));
	int a, b, vexDel;
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for(int i=0;i<G->arcnum;i++){
		scanf("%d%d", &a, &b);
		addArc(G, a, b);
	}
	scanf("%d", &vexDel);
	
	DFSgraph(G);
	BFSgraph(G);
	delVex(G, vexDel);
	
	DFSgraph(G);
	BFSgraph(G);
	return 0;
}
