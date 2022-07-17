//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

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
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step==1) ? print1(): 1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root): 2; 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3(): 3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4(): 4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

void statCount()
{
	Ccount[0] = 1;
	char c;
	while((c = fgetc(Src)) != EOF){
		Ccount[(int)c]++;
	}
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

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

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

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

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

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

//��ʵ�鲽��4������

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
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
