#include<stdio.h>
#include<stdlib.h>
typedef int Element;
typedef struct Node{
    Element data;
    Node *next;
}*CLinkList,Node;

//测试用例
void test_all_function();    //测试用例-测试所有函数

//主功能
bool InitList(CLinkList& list);    //初始化链表
Node* GetNode();    //获取一个节点
bool isTail(CLinkList list,Node* node);    //判断是否到达表尾
bool InsertNextNode(Node* node,Element element);    //插入节点
bool Empty(CLinkList list);    //判断表是否为空
Node* GetFirstNode(CLinkList list);    //获取表的第一个节点
bool PrintList(CLinkList list);    //遍历链表
bool DeleteNextNode(CLinkList list,Node* node);    //删除节点
int main(){
    test_all_function();
    return 0;
}

/**
 * 测试用例
 */
void test_all_function(){
    CLinkList list;
    InitList(list);
    bool isSuccess = false;
    isSuccess =isTail(list, list);
    printf("是否是尾节点:%d\n", isSuccess);
    isSuccess = InsertNextNode(list, 1);
    InsertNextNode(list, 2);
    printf("插入是否成功:%d\n", isSuccess);
    PrintList(list);

    isSuccess = DeleteNextNode(list,list);
    printf("\n删除成功？:%d\n", isSuccess);
    PrintList(list);
}

/**
 * 删除节点node
 * @param node
 * @return
 */
bool DeleteNextNode(CLinkList list,Node* node){
    if (node == NULL || list == NULL) {
        return false;
    }

    if (isTail(list, node)) {//node节点为表尾
        return false;
    }

    Node *nextNode = node->next;
    node->next = nextNode->next;
    free(nextNode);
    return true;
}

/**
 * 返回链表的首节点
 * @param list 表
 * @return 首节点
 */
Node* GetFirstNode(CLinkList list){
    return list->next;
}

/**
 * 遍历打印单链表
 * @param list 线性表
 * @return 遍历结果
 */
bool PrintList(CLinkList list){
    if (list == NULL) {
        printf("[]");
        return false;
    }
    Node *p;
    p = GetFirstNode(list);
    printf("[");
    while(p!=list){
        printf("%d", p->data);
        //如果当前节点不是尾节点，输出,
        if (!isTail(list,p)) {
            printf(", ");
        }
        p=p->next;
    }
    printf("]");

    return true;
}

/**
 * 判断表list是否为空
 * @param list 表
 * @return 表list是否为空
 */
bool Empty(CLinkList list){
    return list->next == list ? true : false;
}

/**
 * 在节点node后面插入一个节点，节点数据域为element
 * @param node
 * @param element
 * @return
 */
bool InsertNextNode(Node* node,Element element){
    if (node == NULL) {
        return false;
    }

    Node *newNode = GetNode();
    newNode->data = element;
    newNode->next = node->next;
    node->next = newNode;
    return true;
}

/**
 * 判断节点node是否是表list的表尾节点
 * 当节点node的next等于list时，表示当前节点为尾节点
 * @param list 表
 * @param node 判断节点
 * @return 节点node是否是表list的表尾节点
 */
bool isTail(CLinkList list, Node *node){
    if (list == NULL || node == NULL) {
        return false;
    }
    //当节点的next等于list时，表示当前节点为尾节点
    return node->next == list ? true : false;
}

/**
 * 初始化链表
 * @param list 表
 * @return 初始化结果
 */
bool InitList(CLinkList &list){
    list = GetNode();
    if (list == NULL) {    //内存分配失败
        return false;
    }
    //将next指向自己
    list->next = list;
    return true;
}

/**
 * 获得一个空节点
 * @return 空节点
 */
Node* GetNode(){
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data=NULL;
    node->next=NULL;
    return node;
}




