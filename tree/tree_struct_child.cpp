/**
 * 以孩子表示法的方式存储树    顺序+链式
 * 顺序存储所有节点，提供一个链域 用于存储孩子节点
 */
#include<stdio.h>
#define MAX_SIZE 100

typedef int ElemType;

//指向孩子的节点
typedef struct ChildNode{
    int index;    //孩子所在的索引
    ChildNode* brother;    //该孩子的兄弟
}ChildNode;

//节点
typedef struct Node{
    ElemType data;    //数据域
    ChildNode* firstChild;    //当前节点的第一个孩子
}Node;

//树
typedef struct Tree{
    Node array[MAX_SIZE];    //节点集合
    int size;    //节点个数
}Tree;





/**
 * 测试用例-测试所有方法
 */
void test_all_function() {

}

int main() {
    test_all_function();
    return 0;
}