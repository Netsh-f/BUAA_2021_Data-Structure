//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
	Ccount[0] = 1;
	char c;
	while((c = fgetc(Src)) != EOF){
		Ccount[(int)c]++;
	}
}

//【实验步骤1】结束

//【实验步骤2】开始

void createHTree()
{
	struct tnode *p, *f[128];
	int cntf = 0, cntc = -1;
	void fsort(){
		for(int i=0;i<cntf-1;i++){
			for(int j=0;j<cntf-1-i;j++){
				if((f[j]->weight < f[j+1]->weight) || (f[j]->weight == f[j+1]->weight && (f[j]->c>=0?f[j]->c:128-f[j]->c) < (f[j+1]->c>=0?f[j+1]->c:128-f[j+1]->c))){
					p = f[j];
					f[j] = f[j+1];
					f[j+1] = p;
				}
			}
		}
	}  
	
	for(int i=0;i<128;i++){
		if(Ccount[i] > 0 && i != '\n'){
			p = (struct tnode*)malloc(sizeof(struct tnode));
			p->c = i;
			p->weight = Ccount[i];
			p->left = p->right = NULL;
			f[cntf++] = p;
		}
	}
	fsort();
	while(cntf > 1){
		p = (struct tnode*)malloc(sizeof(struct tnode));
		p->c = cntc--;
		p->weight = f[cntf-1]->weight + f[cntf-2]->weight;
		p->left = f[cntf-1];
		p->right = f[cntf-2];
		cntf--;
		f[cntf-1] = p;
		fsort();
	}
	Root = f[0];
}

//【实验步骤2】结束

//【实验步骤3】开始

void visitTree(struct tnode *p, char a[], int lena, int dir){
	if(p != NULL){
		if(p != Root)
			a[lena++] = '0' + dir;
		if(p->left == NULL && p->right == NULL){
			a[lena] = '\0';
			strcpy(HCode[(int)p->c], a);
		}
		visitTree(p->left, a, lena, 0);
		visitTree(p->right, a, lena, 1);
	}
}

void makeHCode()
{
	char a[MAXSIZE];
	visitTree(Root, a, 0, 0);
} 

//【实验步骤3】结束

//【实验步骤4】开始

void atoHZIP()
{
	Src=fopen("input.txt","r");
	char s[5005], c;
	unsigned char h = 0;
	int lens = 0, lenh;
	while((c = fgetc(Src)) != EOF){
		if(c == '\n')
			continue;
		lenh = strlen(HCode[(int)c]);
		for(int i=0;i<lenh;i++){
			s[lens++] = HCode[(int)c][i];
		}
	}
	lenh = strlen(HCode[0]);
	for(int i=0;i<lenh;i++){
		s[lens++] = HCode[0][i];
	}
	int i;
	for(i=0;i<lens;i++){
		h = (h<<1)|(s[i]-'0');
		if((i+1)%8 == 0){
			printf("%x", h);
			fputc(h, Obj);
		}
	}
	while(i%8 != 0){
		h = h<<1;
		i++;
		if(i%8 == 0){
			printf("%x", h);
			fputc(h, Obj);
		}
	}
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
