/**
* 使用单链表(不含头结点)形式实现的线性表
*/
#include "stdio.h"
#include "stdlib.h"
typedef int Element;

typedef struct LNode{
    Element data;
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
LNode *getNewNode();
bool ListInsert(LinkList &, int, Element);
void printError(bool,char*);
bool printList(LinkList);

int main(){
    LinkList list;
    InitList(list);
    bool isSuccess = ListInsert(list, 1, 1);
    isSuccess = ListInsert(list, 2, 2);
    printError(isSuccess, "插入");
    printList(list);

    return 0;
}


/**
 * 遍历打印单链表
 * @param list 线性表
 * @return 遍历结果
 */
bool printList(LinkList list){
    if (list == NULL) {
        return false;
    }
    LNode *p;
    p = list;
    while(p!=NULL){
        printf("%d ", p->data);
        p=p->next;
    }

    return true;

}

/**
 * 打印错误信息
 * @param b 是否错误
 * @param msg 错误信息
 */
void printError(bool b,char* msg){
    if(!b){
        printf("%s失败\n", msg);
    }
}

bool ListInsert(LinkList &list, int i, Element element){
    if (i < 1) {
        return false;
    }
    //如果插入节点为头节点
    if (i == 1) {
        LNode* node = getNewNode();
        node->data = element;
        node->next = list;    //将原来的第一个节点连接到新节点上
        list = node;    //头节点替换为新节点
        return true;
    }

    LNode* p;   //位置指针;
    int j = 1;   //第一个位置
    p = list;
    //将指针停留在要插入的位置 前一个位置
    //i-1 代表前一个位置 j表示当前位置
    while (p != NULL && j < i-1) {
        p = p->next;
        j++;
    }

    if (p == NULL) {
        return false;
    }

    LNode* node = getNewNode();
    node->data = element;
    node->next = p->next;
    p->next = node;
    return true;
}

/**
 * 获取的一个新节点
 * @return 一个新节点
 */
LNode* getNewNode(){
    return (LNode *) malloc(sizeof(LNode));
}

/**
 * 初始化线性表
 * @param L 线性表
 * @return 空的线性表
 */
bool InitList(LinkList &L){
    L = NULL;
    return true;
}