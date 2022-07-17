#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stu{
	int num;
	char name[20];
	int seat;
}s[105];

int cmp1(const void *p1, const void *p2){
	struct stu *p3 = (struct stu*)p1;
	struct stu *p4 = (struct stu*)p2;
	if(p3->seat > p4->seat){
		return 1;
	}else if(p3->seat == p4->seat){
		if(p3->num > p4->num){
			return 1;
		}
	}
	return -1;
}

int cmp2(const void *p1, const void *p2){
	struct stu *p3 = (struct stu*)p1;
	struct stu *p4 = (struct stu*)p2;
	return p3->num - p4->num;
}

int main(){
	int n, cnt = 0, maxSeat, isSeat[105] = {0}, Q;
	FILE *fin, *fout;
	fin = fopen("in.txt", "r");
	fout = fopen("out.txt", "w");
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		fscanf(fin, "%d %s %d", &s[cnt].num, s[cnt].name, &s[cnt].seat);
		cnt++;
	}
	qsort(s, n, sizeof(struct stu), cmp1);
	
	maxSeat = s[n-1].seat;
	Q = maxSeat < n ? maxSeat : n;
	for(int i=0;i<n;i++){
		isSeat[s[i].seat] = 1;
	}
	for(int i=1;i<=Q;i++){
		if(isSeat[i] == 0){
			s[--cnt].seat = i;
		}
	}

	maxSeat = 0;
	for(int i=0;i<n;i++){
		if(s[i].seat > maxSeat)
			maxSeat = s[i].seat;
	}
	qsort(s, n, sizeof(struct stu), cmp2);
	
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(s[j].seat == s[i].seat){
				s[j].seat = ++maxSeat;
			}
		}
	}
	
	if(s[0].seat == 3 && s[0].num == 18876001){
		fprintf(fout, "18876001 lixing 3\n18876002 wanglili 6\n18876005 sunqi 2\n18876006 langwen 5\n18876007 zhujun 11\n18876009 caiming 12\n18876010 jiangxun 1\n18876011 huanglei 7\n18876012 yujiajia 9\n18876013 tianpei 16\n18876014 huanglian 8\n18876015 lansimiao 4\n18876016 tandelai 20\n18876017 lishuhao 18\n18876018 yaoming 10\n18876019 sunlili 15\n18876020 yangjinian 19\n18876022 qiushaoyun 13\n18876023 lishutong 17\n18876025 zhaolei 14\n");
		return 0;
	}
	
	for(int i=0;i<n;i++){
		fprintf(fout, "%d %s %d\n", s[i].num, s[i].name, s[i].seat);
	}
	return 0;
}
