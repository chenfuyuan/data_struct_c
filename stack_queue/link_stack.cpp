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
 * 获取栈顶元素
 * @param stack 栈
 * @param elem 元素
 * @return 是否获取成功
 */
bool GetTop(LinkStack stack,ElemType &elem){
    if (StackEmpty(stack)) {
        return false;
    }

    elem = stack->data;    //获取栈顶元素

    return true;
}

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
    LinkStack stack;
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


/**
 * 判断字符是否为数字
 * @param ch 数字
 * @return
 */
bool isNum(char ch){
    return ch >= '0' && ch <= '9';
}


/**
 * 假设字符ch为数字
 * 将字符ch转换为数字int类型
 * @param ch 需要转换的字符
 * @return 转换结果
 */
int char_to_num(char ch){
    return (int)(ch - '0');
}

/**
 * 判断字符是否为运算符
 * @param ch 字符
 * @return 如果字符为运算符则返回true
 */
bool isOpt(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

/**
 * 如果运算符opt_01 优先于 运算符opt_02 则返回true
 * @param opt_01 运算符01
 * @param opt_02 运算符02
 * @return 运算符opt_01是否比 运算符opt_02优先
 */
bool isOptPrior(char opt_01, char opt_02){
    if (opt_01 == '+' || opt_01 == '-') {
        return true;
    }

    if (opt_02 == '*' || opt_02 == '/' || opt_02 == '%') {
        return true;
    }

    return false;
}

/**
 * 进行运算
 * left_num opt right_num = result
 * @param opt 运算符
 * @param left_num 左操作数
 * @param right_num 右操作数
 * @return 运算是否成功
 */
bool opt_calculate(char opt,int left_num,int right_num,int &result){
    //根据操作数，进行不同的运算
    switch (opt) {
        case '+':
            result = left_num + right_num;
            break;
        case '-':
            result = left_num - right_num;
            break;
        case '*':
            result = left_num * right_num;
            break;
        case '/':
            result = left_num / right_num;
            break;
        case '%':
            result = left_num % right_num;
            break;
        default:
            return false;
    }

    return true;
}

/**
 * 计算中序表达式 并将值赋值到result变量中
 * @param str 中序表达式
 * @param result 值
 * @return
 */
bool medium_expression_calculate(char *str,int &result){
    LinkStack opt_stack;    //运算符栈
    LinkStack num_stack;    //操作数栈
    InitStack(opt_stack);
    InitStack(num_stack);
    while (true) {
        char ch = *str;
        if (ch == '\0') {
            break;
        }
        int num = 0;
        //当字符为'-'时且下一个字符为数字时  或 字符为数字时
        if(isNum(ch)) {
            //获取接下来的字符，构建成操作数
            while (true) {
                num *= 10;
                num += char_to_num(ch);
                if (!isNum(*(str + 1))) {
                    break;
                }

                //跳转到下一个字符
                ch = *(++str);
                if (ch == '\0') {
                    break;
                }
            }

            //将操作数入栈
            printf(" %d ", num);
            Push(num_stack, num);
        }

        if (isOpt(ch)) {    //如果字符为运算符
            while (!StackEmpty(opt_stack)) {
                ElemType topElem = -1;
                GetTop(opt_stack, topElem);
                char opt = char(topElem);
                if (!isOptPrior(ch, opt) || is_left_bracket(opt)) {
                    break;
                }
                printf(" %c ", opt);
                Pop(opt_stack, topElem);
                //从操作数栈中，取出2个操作数，进行计算
                int right_opt_num = -1;
                int left_opt_num = -1;

                //获取右操作数
                bool isSuccess = Pop(num_stack, right_opt_num);
                if (!isSuccess) {
                    printf("系统错误，获取右操作数时，失败!\n");
                    return false;
                }

                //获取左操作数
                isSuccess = Pop(num_stack, left_opt_num);
                if (!isSuccess) {
                    printf("系统错误，获取左操作数时，失败!\n");
                    return false;
                }
                int calculate_result = -1;
                isSuccess = opt_calculate(opt, left_opt_num, right_opt_num,calculate_result);
                if (!isSuccess) {
                    printf("系统错误，运算错误!\n");
                    return false;
                }
                Push(num_stack, calculate_result);
            }
            Push(opt_stack, ch);
        }

        if (is_left_bracket(ch)) {
            Push(opt_stack, ch);
        }

        if (is_right_bracket(ch)) {
            //获取操作数栈顶元素，
            ElemType topElem;
            bool isSuccess = Pop(opt_stack, topElem);
            if (!isSuccess) {
                printf("系统错误，获取运算符失败!\n");
                return false;
            }
            char opt = char(topElem);
            printf(" %c ", opt);
            //从操作数栈中，取出2个操作数，进行计算
            int right_opt_num = -1;
            int left_opt_num = -1;

            //获取右操作数
            isSuccess = Pop(num_stack, right_opt_num);
            if (!isSuccess) {
                printf("系统错误，获取右操作数时，失败!\n");
                return false;
            }

            //获取左操作数
            isSuccess = Pop(num_stack, left_opt_num);
            if (!isSuccess) {
                printf("系统错误，获取左操作数时，失败!\n");
                return false;
            }
            int calculate_result = -1;
            isSuccess = opt_calculate(opt, left_opt_num, right_opt_num,calculate_result);
            if (!isSuccess) {
                printf("系统错误，运算错误!\n");
                return false;
            }
            Push(num_stack,calculate_result);
            if (!GetTop(opt_stack, topElem)) {
                printf("系统错误 获取栈顶元素失败!\n");
                return false;
            }
            char bracket = char(topElem);
            if (!is_left_bracket(bracket)) {
                printf("系统错误，括号不匹配!\n");
                return false;
            }
            Pop(opt_stack, topElem);
        }

        str+=1;
    }

    while (!StackEmpty(opt_stack)) {
        if (StackEmpty(num_stack)) {
            printf("系统错误，操作数栈耗尽。\n");
            return false;
        }

        ElemType topElem;
        bool isSuccess = Pop(opt_stack, topElem);
        if (!isSuccess) {
            printf("系统错误,获取运算符错误。\n");
            return false;
        }
        char opt = (char) topElem;
        printf(" %c ", opt);
        if (!isOpt(opt)) {
            printf("系统错误，运算符栈元素非运算符。\n");
            return false;
        }

        //从操作数栈中，取出2个操作数，进行计算
        int right_opt_num = -1;
        int left_opt_num = -1;

        //获取右操作数
        isSuccess = Pop(num_stack, right_opt_num);
        if (!isSuccess) {
            printf("系统错误，获取右操作数时，失败!\n");
            return false;
        }

        //获取左操作数
        isSuccess = Pop(num_stack, left_opt_num);
        if (!isSuccess) {
            printf("系统错误，获取左操作数时，失败!\n");
            return false;
        }
        int calculate_result = -1;
        isSuccess = opt_calculate(opt, left_opt_num, right_opt_num,calculate_result);
        if (!isSuccess) {
            printf("系统错误，运算错误!\n");
            return false;
        }
        Push(num_stack,calculate_result);
    }

    if (StackEmpty(num_stack)) {
        printf("系统错误,计算没有结果\n");
        return false;
    }

    Pop(num_stack, result);
    if (!StackEmpty(num_stack)) {
        printf("系统错误,计算未完成\n");
        return false;
    }
    printf("\n");
    return true;
}

/**
 * 测试中序表达式求职
 */
void test_medium_expression(){
    int calculate_result = -1;
    char input[30];
    scanf("%s", input);
    bool isSuccess = medium_expression_calculate(input, calculate_result);
    if (!isSuccess) {
        printf("计算错误\n");
        return;
    }
    printf("运算结果:%d", calculate_result);
}

int main() {
    //test_all_function();

    //测试括号匹配
    //test_bracket_match();

    //printf("%d", char_to_num('0'));
    test_medium_expression();
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
