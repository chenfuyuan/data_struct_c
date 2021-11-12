/**
 * 使用 不带头结点单链表的形式，实现队列
 */
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct Node{
    ElemType data;
    Node *next;
}Node;

//定义队列结构体
typedef struct {
    Node *front,*rear;    //包含一个指向表头结点和一个指向表尾的指针
    int size;    //记录队列大小
}Queue;


//定义需要实现的方法
bool Init(Queue &queue);    //初始化
bool Empty(Queue queue);    //判断队列是否为空
//bool Full(Queue queue);    //判断队列是否满，链表实现队列，不存在队列满问题
bool EnQueue(Queue &queue, ElemType elem);    //入队
bool DeQueue(Queue &queue, ElemType &elem);    //出队
int Size(Queue queue);    //获取队列长度
bool Print(Queue queue);    //遍历队列
int GetNextIndex(int index);    //获取下一个位置
Node* GetNewNode();    //获取一个空节点

/**
 * 测试用例-测试所有方法
 */
void test_all_function() {
    //初始化
    Queue queue;
    Init(queue);
    //入队
    EnQueue(queue, 1);
    EnQueue(queue, 2);
    EnQueue(queue, 3);
    printf("入队结果:");
    Print(queue);

    //出队
    ElemType deQueueResult = 0;
    DeQueue(queue, deQueueResult);
    printf("出队元素:%d\n", deQueueResult);
    DeQueue(queue, deQueueResult);
    printf("出队元素:%d\n", deQueueResult);
    DeQueue(queue, deQueueResult);
    printf("出队元素:%d\n", deQueueResult);
    bool isSuccess = DeQueue(queue, deQueueResult);
    if(!isSuccess){
        printf("出队失败。\n");
    }else{
        printf("出队元素:%d\n", deQueueResult);
    }
    printf("出队结果:");
    Print(queue);

}

int main() {
    test_all_function();
    return 0;
}

/**
 * 返回队列queue的大小
 * @param queue 队列
 * @return 队列大小
 */
int Size(Queue queue){
    return queue.size;
}

/**
 * 遍历打印当前队列
 * @param queue 队列
 * @return 遍历结果
 */
bool Print(Queue queue){
    if (Empty(queue)) {
        printf("[] size = %d", Size(queue));
        return true;
    }

    //指向第一个元素
    Node *p = queue.front;

    printf("[");
    while (p != NULL) {
        printf("%d", p->data);

        if (p->next != NULL) {
            printf(", ");
        }
        p = p->next;
    }
    printf("] size = %d\n", Size(queue));
    return true;
}

/**
 * 出队操作
 * 将队列queue表头的元素返回给变量elem中，并将返回的数据从队列中删除
 * @param queue 队列
 * @param elem 元素
 * @return
 */
bool DeQueue(Queue &queue, ElemType &elem){
    //判断表是否为空
    if (Empty(queue)) {
        return false;
    }
    //返回表头元素
    elem = queue.front->data;

    //删除表头元素
    Node *first = queue.front;
    queue.front = first->next;

    //当出队 对象 为队列最后一个元素时，如果使用free直接删除，会导致queue.rear指向丢失，应将queue.rear指向头节点
    if (queue.front == NULL) {
        queue.rear = queue.front;
    }

    free(first);

    //减少队列大小
    queue.size--;
    return true;
}

/**
 * 入队操作
 * 将元素elem插入队列queue的尾部
 * @param queue 队列
 * @param elem 元素
 * @return 是否插入成功
 */
bool EnQueue(Queue &queue, ElemType elem){
    Node *node = GetNewNode();
    if (node == NULL) {
        return false;
    }
    //插入表尾
    node->data = elem;

    if (Empty(queue)) {
        queue.front = queue.rear = node;
    }else{
        queue.rear->next = node;
        //尾节点后移
        queue.rear = node;
    }

    //队列大小增加
    queue.size++;
    return true;
}

/**
 * 判断队列是否为空
 * @param queue 队列
 * @return 如果队列为空，则返回true
 */
bool Empty(Queue queue){
    return queue.front == NULL;
}

/**
 * 获取一个空节点
 * @return 空节点
 */
Node* GetNewNode(){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = 0;
    node->next = NULL;
}

/**
 * 初始化队列
 * @param queue 需要初始化的队列
 * @return 初始化是否成功
 */
bool Init(Queue &queue){
    queue.front = NULL;
    queue.rear = NULL;
    queue.size = 0;
}