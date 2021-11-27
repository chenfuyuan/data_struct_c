/**
 * 十字链表(用于存储有向图)
 */
#include<stdio.h>
#define MAX_SIZE 100

typedef int ElemType;
typedef int InfoType;
//边
typedef struct EdgeNode{
    InfoType info;    //权值
    int tailvex;    //弧尾
    int headvex;    //弧头
    EdgeNode *tlink;    //同一个弧尾的下一条边
    EdgeNode *hlink;    //同一个弧头的下一条边
}EdgeNode;

//顶点
typedef struct VertexNode{
    ElemType data;    //数据域
    EdgeNode *first;    //相邻的第一条边
}VertexNode;

//十字链表
typedef struct List{
    VertexNode array[MAX_SIZE];    //顶点列表
    int vertex_num,edge_num;    //顶点数，边数
};

/**
 * 测试用例-测试所有方法
 */
void test_all_function() {

}

int main() {
    test_all_function();
    return 0;
}