/**
 * no_direction_adjacent_matrix 无向图邻接矩阵
 * adjacent 邻接的
 * matrix 矩阵
 *
 * 使用邻接矩阵表示无向图
 */
#include<stdio.h>
#define MAX_SIZE 100

typedef int ElemType;    //定义元素类型


typedef struct Node{
    ElemType data;    //数据域
    bool isEmpty;    //是否为空
    int info;    //权值
}Node;

typedef struct Matrix{
    Node array[MAX_SIZE][MAX_SIZE];    //使用二维数组存储图
    int vertex_num, edge_num;    //顶点数，边数
}Matrix;



/**
 * 测试用例-测试所有方法
 */
void test_all_function() {

}

int main() {
    test_all_function();
    return 0;
}