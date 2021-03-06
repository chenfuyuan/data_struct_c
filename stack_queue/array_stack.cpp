#include<stdio.h>
#define MaxSize 10
#define array_size(array) (sizeof(array)/sizeof(array[0]))
typedef char ElemType;
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

/**
 * 判断是否是左括号
 * @return 如果是左括号，则返回true
 */
bool is_left_bracket(char ch){
    return ch == '{' || ch == '[' || ch == '(';
}

/**
 * 判断是否是右括号
 * @return 如果是右括号，则返回true
 */
bool is_right_bracket(char ch){
    return ch == '}' || ch == ']' || ch == ')';
}

/**
 * 判断字符是否为括号
 * @param ch 字符
 * @return 如果为括号返回true
 */
bool is_bracket(char ch){
    return is_left_bracket(ch) || is_right_bracket(ch);
}

/**
 * 假设left_bracket和right_brakcet 两个字符 都为括号
 * 将左括号left_bracket 与 右括号right_bracket 进行匹配，如果匹配成功，返回true,否则返回false
 * @param left_bracket 左括号
 * @param right_bracket 右括号
 * @return 是否匹配成功
 */
bool match(char left_bracket, char right_bracket){
    if (!is_left_bracket(left_bracket)) {
        printf("匹配括号时发生错误:{%s}不为左括号!\n", left_bracket);
        return false;
    }
    if (!is_right_bracket(right_bracket)) {
        printf("匹配括号时发生错误:{%s}不为右括号!\n", right_bracket);
        return false;
    }

    if (left_bracket == '{' && right_bracket == '}') {
        return true;
    }

    if (left_bracket == '[' && right_bracket == ']') {
        return true;
    }

    if (left_bracket == '(' && right_bracket == ')') {
        return true;
    }

    return false;

}

/**
 * 判断输入的字符串str中，括号是否匹配，如果匹配成功返回true,否则返回false
 * @param str 输入的字符串
 * @return 匹配是否成功
 */
bool bracket_match(char *str){
    //初始化栈
    SqStack stack;
    InitStack(stack);
    bool result = false;
    //解析字符串
    char ch = *(str++);
    while (ch != '\0') {
        if (!is_bracket(ch)) {    //如果字符不为括号时，跳过该字符
            ch = *(str++);
            continue;
        }

        if (is_left_bracket(ch)) {
            //如果字符为左括号时，进行入栈操作
            result = Push(stack, ch);
            if (!result) {
                printf("系统错误!(入栈时，栈满)\n");
            }
        }

        if (is_right_bracket(ch)) {
            //如果字符为右括号时，进行出栈操作
            ElemType popResult = ' ';
            result = Pop(stack, popResult);

            //处理出栈结果，如果出栈失败，表示栈内无元素
            if (!result) {
                printf("匹配失败，缺少左括号!\n");
                return false;
            }

            //匹配括号
            if (!match(popResult, ch)) {
                printf("匹配失败。左括号为{%c},右括号为{%c}!\n", popResult, ch);
                return false;
            }
        }

        if (result == false) {
            return result;
        }
        ch = *(str++);
    }

    //在循环后，栈内依然有元素，则表示匹配失败，缺少右括号
    if (!StackEmpty(stack)) {
        while (!StackEmpty(stack)) {
            ElemType popResult = ' ';
            result = Pop(stack, popResult);
            if (!result) {
                printf("系统错误(栈为空)!\n");
                return false;
            }

            printf("缺乏{%c}对应的右括号!\n", popResult);
        }
        return false;
    }
}

/**
 * 应用:括号匹配
 */
void test_bracket_match(){
    char str[30] = {0};
    scanf("%s", str);
    bool result = bracket_match(str);
    printf("匹配成功。\n");
}

int main() {
    //test_all_function();
    test_bracket_match();
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