/**
 * 邻接多重表(用于存储无向图)
 */
#include<stdio.h>
#define MAX_SIZE 100

typedef int ElemType;
typedef int InfoType;    //定义权值类型

//边
typedef struct EdgeNode{
    InfoType info;    //权值
    int i;    //顶点i的索引
    int j;    //顶点j的索引
    EdgeNode * inext;    //依附于顶点i的下一条边
    EdgeNode * jnext;    //依附于顶点j的下一条边
}EdgeNode;

//顶点
typedef struct VertexNode{
    ElemType data;    //数据域
    EdgeNode * first;
}VertexNode;

//邻接多重表
typedef struct Graph{
    VertexNode array[MAX_SIZE];    //顶点列表
    int vertex_num,edge_num;    //顶点数，边数
}Graph;

/**
 * 测试用例-测试所有方法
 */
void test_all_function() {

}

int main() {
    test_all_function();
    return 0;
}