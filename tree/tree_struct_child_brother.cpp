/**
 * 以孩子-兄弟表示法存储树
 */
#include<stdio.h>

typedef int ElemType;

typedef struct Node {
    ElemType data;
    Node *firstChild;    //指向第一个孩子
    Node *sibling;    //指向兄弟
} Node, *Tree;

/**
 * 测试用例-测试所有方法
 */
void test_all_function() {

}

int main() {
    test_all_function();
    return 0;
}