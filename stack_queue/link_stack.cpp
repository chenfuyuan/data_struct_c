#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct Node{
    ElemType data;
    Node *next;    //指向下一个结点
}*LinkStack,Node;

bool InitStack(LinkStack &);    //初始化栈
bool Push(LinkStack&,ElemType);    //进栈
bool Pop(LinkStack&,ElemType&);    //出栈
bool GetTop(LinkStack, ElemType &);    //获取栈顶元素
bool StackEmpty(LinkStack);    //判断栈是否为空
bool PrintStack(LinkStack);    //打印栈
Node* GetNode();    //获取一个新结点

/**
 * 测试用例-测试所有方法
 */
void test_all_function(){
    LinkStack stack;
    InitStack(stack);
    Push(stack, 1);
    Push(stack, 2);
    printf("进栈结果:");
    PrintStack(stack);
    ElemType popResult = 0;
    Pop(stack, popResult);
    printf("弹出的元素为%d\n", popResult);
    Pop(stack, popResult);
    printf("弹出的元素为%d\n", popResult);

    printf("出栈结果");
    PrintStack(stack);
}

int main() {
    test_all_function();
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


/**
 * 将栈stack的栈顶元素赋值到elem上后进行删除
 * @param stack 栈
 * @param elem 元素
 * @return 删除栈顶元素结果
 */
bool Pop(LinkStack &stack,ElemType &elem){
    //判断栈是否为空
    if (StackEmpty(stack)) {
        printf("栈为空。\n");
        return false;
    }

    elem = stack->data;   //获取栈顶元素
    Node* topNode = stack;

    stack = stack->next;    //删除第一个结点
    free(topNode);    //释放第一个结点的内存地址

    return true;
}



/**
 * 将元素elem添加到栈stack中
 * @param stack 栈
 * @param elem 元素
 * @return 是否添加成功
 */
bool Push(LinkStack &stack, ElemType elem){
    Node *node = GetNode();
    if (node == NULL) {    //分配内存失败
        return false;
    }

    //无头节点的头插法
    node->data = elem;
    node->next = stack;    //将第一个节点 链接到新节点后面
    stack = node;    //将新节点替换为第一个节点
    return true;
}
/**
 * 判断栈是否为空
 * @param stack 栈
 * @return 栈为空返回true
 */
bool StackEmpty(LinkStack stack){
    return stack == NULL;
}

/**
 * 初始化栈
 * 将栈顶指针置为-1，静态数组进行初始化
 * @param stack 需要初始化的栈
 * @return 初始化结果
 */
bool InitStack(LinkStack &stack){
    stack = NULL;
    return true;
}

/**
 * 打印栈
 * @param stack 栈
 * @return 打印结果
 */
bool PrintStack(LinkStack stack){
    if (StackEmpty(stack)) {
        printf("[]");
        return true;
    }
    printf("[");
    while (stack!=NULL) {
        printf("%d",stack->data);
        if (stack->next!=NULL) {
            printf(", ");
        }
        stack = stack->next;
    }
    printf("]\n");
    return true;
}
