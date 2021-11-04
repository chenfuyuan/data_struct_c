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
bool InitList(LinkList&);    //初始化表
LNode *getNewNode();    //获取一个新节点
bool ListInsert(LinkList &, int, Element);    //按位置进行节点插入
void printError(bool,char*);    //打印错误
bool printList(LinkList);     //遍历链表
bool InsertNextNode(LNode *, Element);    //将元素插入指定节点(后插)
bool InsertPriorNode(LNode *, Element);    //将元素插入指定节点(前插)
bool ListDelete(LinkList &, int, Element&);    //按位置删除元素
LNode* getPriorNode(LinkList &, int);    //获取指定位置 前一个节点
bool DeleteNode(LNode *&);    //删除指定节点
int main(){
    LinkList list;
    InitList(list);
    bool isSuccess = ListInsert(list, 1, 1);
    isSuccess = ListInsert(list, 2, 2);
    ListInsert(list, 3, 3);
    printError(isSuccess, "插入");
    printList(list);

    Element deleteReuslt = 0;
    isSuccess = ListDelete(list, 3, deleteReuslt);
    printError(isSuccess, "删除失败");
    printf("\ndeleteResult:%d\n", deleteReuslt);
    printf("删除后的表:");
    printList(list);


    isSuccess = DeleteNode(list->next);
    printError(isSuccess, "删除节点");
    printf("\n删除节点后结果:");
    printList(list);

    return 0;
}

bool DeleteNode(LNode *&node){
    if (node == NULL) {
        return false;
    }

    if (node->next == NULL) {
        free(node);
        node = NULL;
        return true;
    }

    LNode *nextNode = node->next;

    node->data = nextNode->data;
    node->next =nextNode->next;
    free(nextNode);
    return true;
}

/**
 * 获取表list 第i个位置 前一个节点
 * @param list 表
 * @param i 位置
 * @return 表list第i个位置的前一个节点
 */
LNode* getPriorNode(LinkList &list, int i){
    LNode *p = list;
    int j = 1;   //不带头节点，所以j指向第一个节点 节点位置为1
    while (p != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    return p;
}

bool ListDelete(LinkList &list, int i, Element &element){
    if (i < 1) {
        return false;
    }

    if (i == 1) {
        LNode *firstNode = list;
        list = firstNode->next;
        free(firstNode);
        return true;
    }

    LNode *p = getPriorNode(list, i);
    element = p->next->data;    //提取要被删除的数据
    return DeleteNode(p->next);    //删除节点
}

/**
 * 将元素element插入节点node的前一个节点
 * @param node 节点
 * @param element 插入元素
 * @return 是否插入成功
 */
bool InsertPriorNode(LNode *node, Element element) {
    if (node == NULL) {
        return false;
    }
    //声明一个新节点，链接到node节点后面
    LNode *newNode = getNewNode();
    newNode->next = node->next;
    node->next = newNode;

    //交换数据域
    Element temp = node->data;
    node->data = element;
    newNode->data = temp;
    return true;
}

/**
 * 将元素element插入节点node的下一个节点
 * @param node 节点
 * @param element 插入元素
 * @return 是否插入成功
 */
bool InsertNextNode(LNode *node, Element element){
    if (node == NULL) {
        return false;
    }

    LNode *newNode = getNewNode();
    newNode->data = element;
    newNode->next = node->next;
    node->next = newNode;
    return true;
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

/**
 * 向表list的第index个位置，插入元素element
 * @param list 线性表
 * @param i 插入位置
 * @param element 插入元素
 * @return 是否插入成功
 */
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

    return InsertNextNode(p, element);
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