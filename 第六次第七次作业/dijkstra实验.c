#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1005

struct arcNode{
	int weight;
	int line;
}arc[MAX][MAX];

struct vexNode{
	char name[105];
	int state;
	int lastvex;
}vex[MAX];

int vexnum;
int dist[MAX];
int visited[MAX];

int located(char name[]){
	for(int i=0;i<vexnum;i++){
		if(strcmp(name, vex[i].name) == 0){
			return i;
		}
	}
	return vexnum;
}

void addArc(char name1[], char name2[], int line){
	int i = located(name1);
	int j = located(name2);
	arc[i][j].line = line;
	arc[i][j].weight = 1;
	arc[j][i].line = line;
	arc[j][i].weight = 1;
}

int dijkstra(int x, int y){
	int index;
	for(int i=0;i<vexnum;i++){
		index = -1;
		dist[x] = 0;
		for(int j=0;j<vexnum;j++){
			if(!visited[j] && (index == -1 || dist[j] < dist[index])){
				index = j;
			}
		}
		//printf("%d: index=%d dist=%d\n", i, index, dist[index]);//----------------
		if(index == y)
			return dist[y];
		visited[index] = 1;
		for(int j=0;j<vexnum;j++){
			if(dist[index] + arc[index][j].weight < dist[j]){
				dist[j] = dist[index] + arc[index][j].weight;
				vex[j].lastvex = index;
				//printf("update %d dist = %d\n", j, dist[j]);
			}
		}
	}
	
	if(dist[y] == 0x3f3f3f3f){
		return -1;
	}
	return dist[y];
}

int main(){
	FILE *f = fopen("bgstations.txt", "r");
	int lineNum, line, stationNum, state;
	char name[105], lastname[105], initialname[105];
	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
			arc[i][j].weight = 0x3f3f3f3f;
	memset(dist, 0x3f3f3f3f, sizeof(dist[0])*MAX);
	fscanf(f, "%d", &lineNum);
	for(int i=0;i<lineNum;i++){
		fscanf(f, "%d%d", &line, &stationNum);
		for(int j=0;j<stationNum;j++){
			fscanf(f, "%s %d", name, &state);
			if(state == 0){
				vex[vexnum].state = state;
				strcpy(vex[vexnum++].name, name);
			}else{
				if(located(name) == vexnum){
					vex[vexnum].state = state;
					strcpy(vex[vexnum++].name, name);
				}
			}
			if(j == 0){
				strcpy(initialname, name);
			}else{
				addArc(lastname, name, line);
			}
			strcpy(lastname, name);
		}
	}
	
	char departure[105], destination[105];
	scanf("%s %s", departure, destination);
	int x = located(departure), y = located(destination);
	dijkstra(x, y);
	
	int ansvex[MAX];
	int anslinenum[MAX];
	int ansline[MAX];
	int anscnt = 0;
	int flag = 0;
	
	for(int i=y;i!=x;i=vex[i].lastvex){
		if(flag == 0){
			ansvex[anscnt] = i;
			ansline[anscnt] = arc[i][vex[i].lastvex].line;
			anslinenum[anscnt]++;
			flag = 1;
		}else{
			if(arc[i][vex[i].lastvex].line == ansline[anscnt]){
				anslinenum[anscnt]++;
			}else{
				anscnt++;
				ansvex[anscnt] = i;
				ansline[anscnt] = arc[i][vex[i].lastvex].line;
				anslinenum[anscnt]++;
			}
		}
	}
	
	printf("%s", vex[x].name);
	for(int i=anscnt;i>=0;i--){
		printf("-%d(%d)-%s", ansline[i], anslinenum[i], vex[ansvex[i]].name);
	}
	return 0;
}
