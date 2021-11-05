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
bool InitList(LinkList&);    //初始化表
LNode *getNewNode();    //获取一个新节点
bool ListInsert(LinkList &, int, Element);    //按位置进行节点插入
void printError(bool,char*);    //打印错误
bool printList(LinkList);     //遍历链表
bool InsertNextNode(LNode *, Element);    //将元素插入指定节点(后插)
bool InsertPriorNode(LNode *, Element);    //将元素插入指定节点(前插)
bool ListDelete(LinkList &, int, Element&);    //按位置删除元素
bool DeleteNode(LNode* &);    //删除节点
LNode *GetElem(LinkList, int);    //按位查找
LNode *LocateElem(LinkList,Element);    //按值查找
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


    isSuccess = DeleteNode(list->next->next);
    printError(isSuccess, "删除节点");
    printf("\n删除节点后结果:");
    printList(list);
    printf("\n");

    LNode *locateElemNode = LocateElem(list, 1);
    if(locateElemNode!=NULL) {
        printf("element{1} = %d",locateElemNode->data);
    } else {
        printf("根据值未找到节点");
    }

    return 0;
}

/**
 * 按值进行查找
 * 查找表list中第一次出现元素element的节点
 * @param list 表
 * @param element 元素
 * @return 查找结果
 */
LNode *LocateElem(LinkList list, Element element){
    if(list == NULL){
        return NULL;
    }
    LNode *p = list->next;    //指向第1个节点
    //遍历链表并判断值是否相等
    while (p != NULL && p->data != element) {
        p = p->next;
    }
    return p;
}


/**
 * 按位查找
 * 查找表list的第i个位置的节点
 * @param list 表
 * @param i 位置
 * @return  表第i位的节点
 */
LNode *GetElem(LinkList list, int i) {
    if (i < 0) {
        return NULL;
    }
    int j = 0;    //代表当前指针 指到表第0个位置，即头结点
    LNode *p = list;    //指向头结点的指针
    //遍历指针到第i个位置
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }

    return p;
}


/**
 * 删除节点
 * @param node 节点
 * @return 删除结果
 */
bool DeleteNode(LNode* &node){
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
 * 将表list的第i个位置的元素删除，并赋值到element变量中进行返回
 * @param list 表
 * @param i 要删除元素的位置
 * @param element 放置删除元素的变量
 * @return 是否删除成功
 */
bool ListDelete(LinkList &list, int i, Element &element){
    if (i < 1) {
        return false;
    }

    //寻找位置i的前一个节点
    LNode *p = GetElem(list, i-1);

    //i值不合法
    if (p == NULL) {
        return false;
    }

    //第i个位置本来就是空的
    if (p->next == NULL) {
        return false;
    }

    element = p->next->data;    //提取要被删除的数据
    return DeleteNode(p->next);    //删除节点
    /*
    LNode* nextNode = p->next;    //要被删除的节点
    element = nextNode->data;    //提取要被删除的数据
    //删除元素
    p->next = nextNode->next;
    free(nextNode);
    return true;
     */

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
    if (newNode == NULL) {    //内存分配失败
        return false;
    }
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
    p = list->next;
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
    p = GetElem(list, i-1);    //找到第i-1位置的节点

    //插入位置超过 链表长度
    if(p==NULL) {
        return false;
    }

    //插入元素
    return InsertNextNode(p, element);
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