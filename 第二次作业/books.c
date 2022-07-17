#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct book{
	char name[55];
	char author[25];
	char press[35];
	char date[15];
};

struct book a[505];
int cnt = 0;

int cmp(const void *x, const void *y){
	struct book *p = (struct book*)x;
	struct book *q = (struct book*)y;
	return strcmp(p->name, q->name);
}

void search(char *b){
	for(int i=0; i<cnt; i++){
		if(strstr(a[i].name, b) != NULL){
			printf("%-50s%-20s%-30s%-10s\n", a[i].name, a[i].author, a[i].press, a[i].date);
		}
	}
}

void del(char *b){
	for(int i=0; i<cnt; i++){
		if(strstr(a[i].name, b) != NULL){
			a[i] = a[cnt-1];
			cnt--;
			i--;
		}
	}
	qsort(a, cnt, sizeof(a[0]), cmp);
}

void display(){
	for(int i=0; i<cnt; i++){
		printf("%-50s%-20s%-30s%-10s\n", a[i].name, a[i].author, a[i].press, a[i].date);
	}
}

int main(){
	FILE *fin = NULL, *fout = NULL;
	char buf[200];
	int op = 1;
	if((fin = fopen("books.txt", "r")) == NULL){
		printf("in error\n");
		return 0;
	}
	if((fout = fopen("ordered.txt", "w")) == NULL){
		printf("out error\n");
		return 0;
	}
	while(fgets(buf, 200, fin) != NULL){
		sscanf(buf, "%s%s%s%s", a[cnt].name, a[cnt].author, a[cnt].press, a[cnt].date);
		cnt++;
	}
	qsort(a, cnt, sizeof(a[0]), cmp);
	
	while(op != 0){
		scanf("%d", &op);
		if(op == 1){
			scanf("%s%s%s%s", a[cnt].name, a[cnt].author, a[cnt].press, a[cnt].date);
			cnt++;
			qsort(a, cnt, sizeof(a[0]), cmp);
		}else if(op == 2){
			scanf("%s", buf);
			search(buf);
		}else if(op == 3){
			scanf("%s", buf);
			del(buf);
		}else if(op == 4){
			display();
		}
	}
	
	for(int i=0; i<cnt; i++){
		sprintf(buf, "%-50s%-20s%-30s%-10s\n", a[i].name, a[i].author, a[i].press, a[i].date);
		fputs(buf, fout);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
