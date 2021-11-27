/**
 * no_direction_adjacent_table 无向图邻接表
 *
 * 使用邻接表结构存储无向图
 */
#include<stdio.h>
#define MAX_SIZE 100

typedef int ElemType;    //定义元素类型

typedef struct EdgeNode{
    int adjvex_index;    //边指向的顶点在顺序存储中的索引
    EdgeNode *next;    //下一条边
}EdgeNode;

//顶点
typedef struct VertexNode{
    ElemType data;    //数据域
    EdgeNode *first;    //与该节点相邻的第一条边
}VertexNode;

//邻接表
typedef struct List{
    VertexNode array[MAX_SIZE];    //顶点数组
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