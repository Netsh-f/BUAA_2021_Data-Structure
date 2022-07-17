#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2005

int cost;

struct arcNode{
	int initial;
	int end;
	int id;
	int weight;
};

struct graph{
	int vexnum, arcnum;
	struct arcNode arc[MAX];
};

int cmp(const void *p1, const void *p2){
	return ((struct arcNode*)p1)->weight - ((struct arcNode*)p2)->weight;
}

int cmp1(const void *p1, const void *p2){
	return ((struct arcNode*)p1)->id - ((struct arcNode*)p2)->id;
}

void kruskal(struct graph *G, struct arcNode minTree[]){
	int assists[MAX], initial, end, cnt = 0, elem;
	for(int i=0;i<G->vexnum;i++){
		assists[i] = i;
	}
	qsort(G->arc, G->arcnum, sizeof(G->arc[0]), cmp);
	for(int i=0;i<G->arcnum;i++){
		initial = G->arc[i].initial;
		end = G->arc[i].end;
		if(assists[initial] != assists[end]){
			minTree[cnt++] = G->arc[i];
			cost += G->arc[i].weight;
			elem = assists[end];
			for(int j=0;j<G->vexnum;j++){
				if(assists[j] == elem){
					assists[j] = assists[initial];
				}
			}
			if(cnt == G->vexnum-1){
				break;
			}
		}
	}
}

int main(){
	struct arcNode minTree[MAX];
	struct graph *G = (struct graph*)malloc(sizeof(struct graph));
	scanf("%d%d", &G->vexnum, &G->arcnum);
	for(int i=0;i<G->arcnum;i++){
		scanf("%d%d%d%d", &G->arc[i].id, &G->arc[i].initial, &G->arc[i].end, &G->arc[i].weight);
	}
	kruskal(G, minTree);
	qsort(minTree, G->vexnum-1, sizeof(minTree[0]), cmp1);
	printf("%d\n", cost);
	for(int i=0;i<G->vexnum-1;i++){
		printf("%d ", minTree[i].id);
	}
	return 0;
}
