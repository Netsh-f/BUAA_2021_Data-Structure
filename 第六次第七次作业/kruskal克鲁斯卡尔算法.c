#include <stdio.h>
#include <stdlib.h>
#define N 9   // 图中边的数量
#define P 6   // 图中顶点的数量
//构建表示边的结构体
struct edge {
    //一条边有 2 个顶点
    int initial;
    int end;
    //边的权值
    int weight;
};
//qsort排序函数中使用，使edges结构体中的边按照权值大小升序排序
int cmp(const void* a, const void* b) {
    return  ((struct edge*)a)->weight - ((struct edge*)b)->weight;
}
//克鲁斯卡尔算法寻找最小生成树，edges 存储用户输入的图的各个边，minTree 用于记录组成最小生成树的各个边
void kruskal_MinTree(struct edge edges[], struct edge minTree[]) {
    int i, initial, end, elem, k;
    //每个顶点配置一个标记值
    int assists[P];
    int num = 0;
    //初始状态下，每个顶点的标记都不相同
    for (i = 0; i < P; i++) {
        assists[i] = i;
    }
    //根据权值，对所有边进行升序排序
    qsort(edges, N, sizeof(edges[0]), cmp);
    //遍历所有的边
    for (i = 0; i < N; i++) {
        //找到当前边的两个顶点在 assists 数组中的位置下标
        initial = edges[i].initial - 1;
        end = edges[i].end - 1;
        //如果顶点位置存在且顶点的标记不同，说明不在一个集合中，不会产生回路
        if (assists[initial] != assists[end]) {
            //记录该边，作为最小生成树的组成部分
            minTree[num] = edges[i];
            //计数+1
            num++;
            elem = assists[end];
            //将新加入生成树的顶点标记全部改为一样的
            for (k = 0; k < P; k++) {
                if (assists[k] == elem) {
                    assists[k] = assists[initial];
                }
            }
            //如果选择的边的数量和顶点数相差1，证明最小生成树已经形成，退出循环
            if (num == P - 1) {
                break;
            }
        }
    }
}
void display(struct edge minTree[]) {
    int cost = 0, i;
    printf("最小生成树为:\n");
    for (i = 0; i < P - 1; i++) {
        printf("%d-%d  权值：%d\n", minTree[i].initial, minTree[i].end, minTree[i].weight);
        cost += minTree[i].weight;
    }
    printf("总权值为：%d", cost);
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
