#include<stdio.h>
#define MaxSize 10
#define array_size(array) (sizeof(array)/sizeof(array[0]))
typedef int ElemType;
typedef struct{
    ElemType data[MaxSize];    //静态数组存储栈元素
    int top;    //指向栈顶指针
}SqStack;

bool InitStack(SqStack &);    //初始化栈
bool Push(SqStack&,ElemType);    //进栈
bool Pop(SqStack&,ElemType&);    //出栈
bool GetTop(SqStack, ElemType &);    //获取栈顶元素
bool StackEmpty(SqStack);    //判断栈是否为空
bool StackFull(SqStack);    //判断栈是否已满
bool PrintStack(SqStack);    //打印栈

void test_all_function(){
    SqStack stack;
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
 * 将栈stack的栈顶元素赋值到elem上后进行删除
 * @param stack 栈
 * @param elem 元素
 * @return 删除栈顶元素结果
 */
bool Pop(SqStack &stack,ElemType &elem){
    //判断栈是否为空
    if (StackEmpty(stack)) {
        printf("栈为空。\n");
        return false;
    }

    elem = stack.data[stack.top];
    stack.top--;
    return true;
}

/**
 * 判断栈是否满
 * @param stack 栈
 * @return 栈满了返回true
 */
bool StackFull(SqStack stack){
    return stack.top== array_size(stack.data) -1;
}

/**
 * 将元素elem添加到栈stack中
 * @param stack 栈
 * @param elem 元素
 * @return 是否添加成功
 */
bool Push(SqStack &stack, ElemType elem){
    //判断栈是否满
    if (StackFull(stack)) {
        printf("栈已满。\n");
        return false;
    }
    stack.top++;
    stack.data[stack.top] = elem;
    return true;
}
/**
 * 判断栈是否为空
 * @param stack 栈
 * @return 栈为空返回true
 */
bool StackEmpty(SqStack stack){
    return stack.top == -1;
}

/**
 * 初始化栈
 * 将栈顶指针置为-1，静态数组进行初始化
 * @param stack 需要初始化的栈
 * @return 初始化结果
 */
bool InitStack(SqStack &stack){
    stack.top = -1;
    for (int i = 0; i < array_size(stack.data); ++i) {
        stack.data[i] = 0;
    }
    return true;
}

/**
 * 打印栈
 * @param stack 栈
 * @return 打印结果
 */
bool PrintStack(SqStack stack){
    int top = stack.top;
    if (StackEmpty(stack)) {
        printf("[]");
        return true;
    }
    printf("[");
    while (top != -1) {
        printf("%d",stack.data[top]);
        if (top != 0) {
            printf(", ");
        }
        top--;
    }
    printf("]\n");
    return true;
}