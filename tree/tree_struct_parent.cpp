/**
 * 使用顺序存储的方式，以双亲表示法的方式存储树
 */
#include<stdio.h>
#define MAX_SIZE 100

typedef int ElemType;    //定义存储的数据类型

//节点
typedef struct Node{
    ElemType data;    //数据域
    int parent;    //指向双亲的索引    根的双亲索引值为-1
};

//树
typedef struct {
    Node array[100];    //存储
    int size;    //大小
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