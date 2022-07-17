#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NHASH  3001
#define MULT  37
char dic[3505][25];
int cntd = 0, front[128];

struct node{
	char str[25];
	struct node *next;
}*head[NHASH];

unsigned int hash(char *str)
{
       unsigned int h=0;
       char *p;
       for(p=str; *p!='\0'; p++)
              h = MULT*h + *p;
       return h % NHASH;
}

void add(char *str){
	struct node *pnew = (struct node*)malloc(sizeof(struct node));
	struct node *p = head[hash(str)];
	strcpy(pnew->str, str);
	pnew->next = NULL;
	if(p == NULL){
		head[hash(str)] = pnew;
		return;
	}
	while(p->next != NULL){
		p = p->next;
	}
	p->next = pnew;
}

int strcmps(char a[], char b[]){
	int lenb = strlen(b);
	for(int i=0;i<lenb;i++){
		if(a[i] > b[i])
			return 1;
		else if(a[i] < b[i])
			return -1;
	}
	return 0;
}

int find1(char s[], int *n){
	int f;
	*n = 0;
	for(int i=0;i<cntd;i++){
		f = strcmps(s, dic[i]);
		(*n)++;
		if(f > 0){
			continue;
		}else if(f == 0){
			return 1;
		}else{
			return 0;
		}
	}
	return 0;
}

int find2(char s[], int *n){
	int l = 0, r = cntd-1, mid, f;
	(*n) = 0;
	while(l <= r){
		mid = (l + r) / 2;
		f = strcmps(s, dic[mid]);
		(*n)++;
		if(f > 0){
			l = mid + 1;
		}else if(f < 0){
			r = mid - 1;
		}else{
			return 1;
		}
	}
	return 0;
}

int find3(char s[], int *n){
	int l = front[(int)s[0]], r = front[(int)s[0]+1]-1, mid, f;
	(*n) = 0;
	while(l <= r){
		mid = (l + r) / 2;
		f = strcmps(s, dic[mid]);
		(*n)++;
		if(f > 0){
			l = mid + 1;
		}else if(f < 0){
			r = mid - 1;
		}else{
			return 1;
		}
	}
	return 0;
}

int find4(char s[], int *n){
	(*n) = 0;
	int f;
	struct node *p = head[hash(s)];
	while(p != NULL){
		f = strcmps(s, p->str);
		(*n)++;
		if(f == 0){
			return 1;
		}else if(f > 0){
			return 0;
		}
		p = p->next;
	}
	return 0;
}

int main(){
	FILE *fp = fopen("dictionary3000.txt", "r");
	char buf[25], c = 'a'-1;
	int op, num, f;
/*	while(fgets(buf, 25, fp) != NULL){
		strcpy(dic[cntd++], buf);
		if(dic[cntd-1][0] > c){
			c = dic[cntd-1][0];
			front[(int)dic[cntd-1][0]] = cntd - 1;
		}
		add(buf);
	}*/
	while(fscanf(fp, "%s", buf) != EOF){
/*		for(int i=0;i<25;i++){
			if(!(buf[i]>='a'&&buf[i]<='z')){
				buf[i] = '\n';
				buf[i+1] = '\0';
				break;
			}
		}*/
		strcpy(dic[cntd++], buf);
		if(dic[cntd-1][0] > c){
			c = dic[cntd-1][0];
			front[(int)dic[cntd-1][0]] = cntd - 1;
		}
		add(buf);
//		memset(buf, 0, sizeof(buf));
	}
	front['z'+1] = cntd;
	while(scanf("%s %d", buf, &op) != EOF){
/*		for(int i=0;i<25;i++){
			if(!(buf[i]>='a'&&buf[i]<='z')){
				buf[i] = '\n';
				buf[i+1] = '\0';
				break;
			}
		}*/
		switch(op){
			case 1:
				f = find1(buf, &num);
				printf("%d %d\n", f, num);
				break;
			case 2:
				f = find2(buf, &num);
				printf("%d %d\n", f, num);
				break;
			case 3:
				f = find3(buf, &num);
				printf("%d %d\n", f, num);
				break;
			case 4:
				f = find4(buf, &num);
				printf("%d %d\n", f, num);
				break;
		}
//		memset(buf, 0, sizeof(buf));
	}
	return 0;
}
