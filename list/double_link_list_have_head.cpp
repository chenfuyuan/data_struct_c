#include<stdio.h>
#include<stdlib.h>
typedef int Element;

typedef struct DNode{
    Element data;    //数据域
    DNode *prior, *next;     //一个指针指向前驱，一个指针指向后继
}*DLinkList,DNode;

bool InitList(DLinkList&);    //初始化链表
DNode* getNode();    //获取一个空节点
bool InsertNextNode(DNode *, Element);    //在一个节点后插入数据
void PrintList(DLinkList);    //打印链表
DNode *GetFirstNode(DLinkList);    //获取头节点
bool DeleteNextNode(DNode *);    //删除一个节点

void test_all_function(){
    DLinkList list;
    InitList(list);
    InsertNextNode(list, 1);
    InsertNextNode(list->next, 2);
    InsertNextNode(list->next->next, 3);
    PrintList(list);

    DeleteNextNode(list->next->next);
    PrintList(list);

}

int main(){
    test_all_function();
    return 0;
}

/**
 * 删除一个节点
 * @param node
 * @return
 */
bool DeleteNextNode(DNode* node){
    if (node == NULL) {
        return false;
    }

    DNode *nextNode = node->next;
    if (nextNode == NULL) {    //判断node是否为表尾
        return false;
    }

    node->next = nextNode->next;
    if (nextNode->next != NULL) {    //判断删除节点是否为表尾节点
        nextNode->next->prior = node;
    }
    free(nextNode);
    return true;
}

/**
 * 获取表list的第一个节点
 * @param list 表
 * @return 表list的第一个节点
 */
DNode* GetFirstNode(DLinkList list){
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}
/**
 * 打印表list
 * @param list 表
 * @return 打印是否成功
 */
void PrintList(DLinkList list){
    if (list == NULL || list->next == NULL) {
        printf("[]");
    }

    DNode *p;
    p = GetFirstNode(list);
    printf("[");
    while(p!=NULL){
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(", ");
        }
        p=p->next;
    }
    printf("]");
}

/**
 * 在节点node后面插入数据element
 * @param node 节点
 * @param element 数据
 * @return 插入结果
 */
bool InsertNextNode(DNode* node,Element element){
    if (node == NULL) {
        return false;
    }

    DNode *nextNode = getNode();
    nextNode->data = element;
    nextNode->next = node->next;
    nextNode->prior = node;
    if (nextNode->next != NULL) {    //表示当前节点node不为表尾
        nextNode->next->prior = nextNode;
    }
    node->next = nextNode;
    return true;
}

/**
 * 获得一个空节点
 * @return 一个空节点
 */
DNode *getNode(){
    DNode *node = (DNode *) malloc(sizeof(DNode));
    if (node == NULL) {
        return NULL;
    }
    node->data = NULL;
    node->prior = NULL;
    node->next = NULL;
    return node;
}


/**
 * 初始化表
 * @param list 表
 * @return  初始化结果
 */
bool InitList(DLinkList &list){
    list = getNode();
    return list == NULL ? false : true;
}