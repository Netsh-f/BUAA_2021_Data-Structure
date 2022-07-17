#include<stdio.h>
#include<stdlib.h>
#define MAX 1005

int edge[MAX][MAX];
int dist[MAX];
int visited[MAX];

int dijkstra(int n, int m){
	int index = -1;
	for(int i=1;i<=n;i++){
		dist[1] = 0;
		for(int j=1;j<=n;j++){
			if(!visited[j] && (index == -1 || dist[j] < dist[index])){
				index = j;
			}
		}
		visited[index] = 1;
		for(int j=1;j<=n;j++){
			if(dist[index] + edge[index][j] < dist[j]){
				dist[j] = dist[index] + edge[index][j];
			}
		}
	}
	
	if(dist[n] == 0x3f3f3f3f){
		return -1;
	}
	return dist[n];
}



int main(){
	FILE *fin = fopen("bgstations.txt", "r");
	
}
