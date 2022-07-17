#include<stdio.h>
#include<stdlib.h>
#define Max 1005
int visited[Max], path[Max];

struct Mgraph{
	int arc[Max][Max];
	int vexnum, arcnum;
};

void addArc(struct Mgraph *G,int val, int x, int y){
	G->arc[x][y] = val;
	G->arc[y][x] = val;
}

void print(int n){
	for(int i=0;i<n;i++){
		printf("%d ", path[i]);
	}
	printf("\n");
}

void DFS(struct Mgraph *G, int vex, int depth){
	if(vex == G->vexnum-1){
		print(depth);
		return;
	}else{
		for(int i=1;i<G->vexnum;i++){
			if(!visited[i] && G->arc[vex][i]){
				path[depth] = G->arc[vex][i];
				visited[i] = 1;
				DFS(G, i, depth+1);
				visited[i] = 0;
			}
		}
	}
}

int main(){
	int val, x, y;
	struct Mgraph *G = (struct Mgraph*)malloc(sizeof(struct Mgraph));
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for(int i=0;i<G->arcnum;i++){
		scanf("%d%d%d", &val, &x, &y);
		addArc(G, val, x, y);
	}
	DFS(G, 0, 0);
	return 0;
}
