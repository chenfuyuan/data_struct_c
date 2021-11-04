/**
* 使用单链表(含头结点)形式实现的线性表
*/
#include "stdio.h"
#include "stdlib.h"
typedef int Element;

typedef struct LNode{
    Element LNode;
    struct LNode *next;
}*LinkList,LNode;
/*等价于
struct LNode{    //定义单链表结点类型
    Element data;    //数据域
    struct LNode *next;    //指针域
};
typedef struct LNode LNode;    //结点
typedef struct LNode *LinkList;    //线性表
 */

//定义函数
bool InitList(LinkList&);

int main(){
    LinkList list;
    InitList(list);
    return 0;
}

/**
 * 初始化线性表
 * @param L 线性表
 * @return 空的线性表
 */
bool InitList(LinkList &L){
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL) {    //内存不足，分配失败
        return false;
    }
    L->next = NULL;    //头节点暂时没有节点
    return true;
}