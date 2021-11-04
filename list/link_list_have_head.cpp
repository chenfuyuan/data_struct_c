/**
* 使用单链表(含头结点)形式实现的线性表
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
bool InitList(LinkList&);    //初始化线性表
bool ListInsert(LinkList&,int,Element);    //插入数据
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

bool printList(LinkList list){
    if (list == NULL) {
        return false;
    }
    LNode *p;
    p = list->next;
    while(p!=NULL){
        printf("%d ", p->data);
        p=p->next;
    }

    return true;

}

void printError(bool b,char* msg){
    if(!b){
        printf("%s失败\n", msg);
    }
}

/**
 * 获取的一个新节点
 * @return 一个新节点
 */
LNode* getNewNode(){
    return (LNode *) malloc(sizeof(LNode));
}

/**
 * 向表list的第index个位置，插入元素element
 * @param list 线性表
 * @param i 插入位置
 * @param element 插入元素
 * @return 是否插入成功
 */
bool ListInsert(LinkList &list, int i, Element element){
    if(i < 1) {
        return false;
    }
    LNode *p;
    int j=0;
    p = list;
    //将指针移动到 i-1 位置
    while(p != NULL && j < i - 1){
        p = p->next;
        j++;
    }

    //插入位置超过 链表长度
    if(p==NULL) {
        return false;
    }

    //插入元素
    LNode *node = getNewNode();   //初始化节点
    node->data = element;    //赋值元素
    node->next = p->next;    //将原本在i位置的节点，链接到新节点的后面
    p->next = node;    //将新节点链接到i位置

    return true;
}

/**
 * 初始化线性表
 * @param L 线性表
 * @return 空的线性表
 */
bool InitList(LinkList &L){
    L = getNewNode();
    if (L == NULL) {    //内存不足，分配失败
        return false;
    }
    L->next = NULL;    //头节点暂时没有节点
    return true;
}