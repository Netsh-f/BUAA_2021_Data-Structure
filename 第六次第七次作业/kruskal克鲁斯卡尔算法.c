#include <stdio.h>
#include <stdlib.h>
#define N 9   // ͼ�бߵ�����
#define P 6   // ͼ�ж��������
//������ʾ�ߵĽṹ��
struct edge {
    //һ������ 2 ������
    int initial;
    int end;
    //�ߵ�Ȩֵ
    int weight;
};
//qsort��������ʹ�ã�ʹedges�ṹ���еı߰���Ȩֵ��С��������
int cmp(const void* a, const void* b) {
    return  ((struct edge*)a)->weight - ((struct edge*)b)->weight;
}
//��³˹�����㷨Ѱ����С��������edges �洢�û������ͼ�ĸ����ߣ�minTree ���ڼ�¼�����С�������ĸ�����
void kruskal_MinTree(struct edge edges[], struct edge minTree[]) {
    int i, initial, end, elem, k;
    //ÿ����������һ�����ֵ
    int assists[P];
    int num = 0;
    //��ʼ״̬�£�ÿ������ı�Ƕ�����ͬ
    for (i = 0; i < P; i++) {
        assists[i] = i;
    }
    //����Ȩֵ�������б߽�����������
    qsort(edges, N, sizeof(edges[0]), cmp);
    //�������еı�
    for (i = 0; i < N; i++) {
        //�ҵ���ǰ�ߵ����������� assists �����е�λ���±�
        initial = edges[i].initial - 1;
        end = edges[i].end - 1;
        //�������λ�ô����Ҷ���ı�ǲ�ͬ��˵������һ�������У����������·
        if (assists[initial] != assists[end]) {
            //��¼�ñߣ���Ϊ��С����������ɲ���
            minTree[num] = edges[i];
            //����+1
            num++;
            elem = assists[end];
            //���¼����������Ķ�����ȫ����Ϊһ����
            for (k = 0; k < P; k++) {
                if (assists[k] == elem) {
                    assists[k] = assists[initial];
                }
            }
            //���ѡ��ıߵ������Ͷ��������1��֤����С�������Ѿ��γɣ��˳�ѭ��
            if (num == P - 1) {
                break;
            }
        }
    }
}
void display(struct edge minTree[]) {
    int cost = 0, i;
    printf("��С������Ϊ:\n");
    for (i = 0; i < P - 1; i++) {
        printf("%d-%d  Ȩֵ��%d\n", minTree[i].initial, minTree[i].end, minTree[i].weight);
        cost += minTree[i].weight;
    }
    printf("��ȨֵΪ��%d", cost);
}
int main() {
    int i;
    struct edge edges[N], minTree[P - 1];
    for (i = 0; i < N; i++) {
        scanf("%d %d %d", &edges[i].initial, &edges[i].end, &edges[i].weight);
    }
    kruskal_MinTree(edges, minTree);
    display(minTree);
    return 0;
}
